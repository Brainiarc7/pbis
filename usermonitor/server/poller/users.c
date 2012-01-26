/* Editor Settings: expandtabs and use 4 spaces for indentation
 * ex: set softtabstop=4 tabstop=8 expandtab shiftwidth=4: *
 * -*- mode: c, c-basic-offset: 4 -*- */

/*
 * Copyright Likewise Software    2004-2008
 * All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.  You should have received a copy of the GNU General
 * Public License along with this program.  If not, see
 * <http://www.gnu.org/licenses/>.
 *
 * LIKEWISE SOFTWARE MAKES THIS SOFTWARE AVAILABLE UNDER OTHER LICENSING
 * TERMS AS WELL.  IF YOU HAVE ENTERED INTO A SEPARATE LICENSE AGREEMENT
 * WITH LIKEWISE SOFTWARE, THEN YOU MAY ELECT TO USE THE SOFTWARE UNDER THE
 * TERMS OF THAT SOFTWARE LICENSE AGREEMENT INSTEAD OF THE TERMS OF THE GNU
 * GENERAL PUBLIC LICENSE, NOTWITHSTANDING THE ABOVE NOTICE.  IF YOU
 * HAVE QUESTIONS, OR WISH TO REQUEST A COPY OF THE ALTERNATE LICENSING
 * TERMS OFFERED BY LIKEWISE SOFTWARE, PLEASE CONTACT LIKEWISE SOFTWARE AT
 * license@likewisesoftware.com
 */

/*
 * Copyright (C) Likewise Software. All rights reserved.
 *
 * Module Name:
 *
 *        users.c
 *
 * Abstract:
 *
 *        User monitor service for local users and groups
 *
 *        Functions for enumerating and tracking users.
 *
 * Authors: Kyle Stemen <kstemen@likewise.com>
 */
#include <lsa/lsa.h>
#include "includes.h"

static
DWORD
UmnSrvUpdateUser(
    HANDLE hReg,
    HKEY hUsers,
    long long Now,
    struct passwd *pUser
    )
{
    DWORD dwError = 0;
    HKEY hKey = NULL;

    dwError = RegOpenKeyExA(
                hReg,
                hUsers,
                pUser->pw_name,
                0,
                KEY_ALL_ACCESS,
                &hKey);
    if (dwError == LWREG_ERROR_NO_SUCH_KEY_OR_VALUE)
    {
        UMN_LOG_VERBOSE("Adding user '%s' (uid %d)",
                        pUser->pw_name, pUser->pw_uid);

        dwError = RegCreateKeyExA(
            hReg,
            hUsers,
            pUser->pw_name,
            0,
            NULL,
            0,
            KEY_ALL_ACCESS,
            NULL,
            &hKey,
            NULL);
        BAIL_ON_UMN_ERROR(dwError);
    }
    else
    {
        BAIL_ON_UMN_ERROR(dwError);

        UMN_LOG_VERBOSE("Updating user '%s' (uid %d)",
                        pUser->pw_name, pUser->pw_uid);
    }

cleanup:
    if (hKey)
    {
        RegCloseKey(
                hReg,
                hKey);
    }
    return dwError;
    
error:
    goto cleanup;
}

static
DWORD
UmnSrvUpdateGroup(
    HANDLE hReg,
    HKEY hGroups,
    long long Now,
    struct group *pGroup
    )
{
    UMN_LOG_VERBOSE("Updating group '%s' (gid %d)",
                    pGroup->gr_name, pGroup->gr_gid);
    return 0;
}

DWORD
UmnSrvUpdateAccountInfo(
    long long Now
    )
{
    DWORD dwError = 0;
    struct passwd *pUser = NULL;
    struct group *pGroup = NULL;
    HANDLE hLsass = NULL;
    HANDLE hReg = NULL;
    HKEY hUsers = NULL;
    HKEY hGroups = NULL;
    LSA_QUERY_LIST list = { 0 };
    DWORD uid = 0;
    PLSA_SECURITY_OBJECT* ppObjects = NULL;
    // Do not free
    PSTR pDisableLsassEnum = NULL;

    list.pdwIds = &uid;

    dwError = LsaOpenServer(&hLsass);
    BAIL_ON_UMN_ERROR(dwError);

    dwError = RegOpenServer(&hReg);
    BAIL_ON_UMN_ERROR(dwError);

    dwError = RegOpenKeyExA(
                hReg,
                NULL,
                HKEY_THIS_MACHINE "\\Services\\" SERVICE_NAME "\\Parameters\\Users",
                0,
                KEY_ALL_ACCESS,
                &hUsers);
    BAIL_ON_UMN_ERROR(dwError);

    dwError = RegOpenKeyExA(
                hReg,
                NULL,
                HKEY_THIS_MACHINE "\\Services\\" SERVICE_NAME "\\Parameters\\Groups",
                0,
                KEY_ALL_ACCESS,
                &hGroups);
    BAIL_ON_UMN_ERROR(dwError);

    pDisableLsassEnum = getenv("_DISABLE_LSASS_NSS_ENUMERATION");
    if (!pDisableLsassEnum || strcmp(pDisableLsassEnum, "1"))
    {
        /* Note, this code must leak memory.
         *
         * Putenv uses the memory passed to it, that it is it does not copy the
         * string. There is no Unix standard to unset an environment variable,
         * and the string passed to putenv must be accessible as long as the
         * program is running. A static string cannot be used because the
         * container could out live this service. There is no opportunity to
         * free the string before the program ends, because the variable must
         * be accessible for the duration of the program.
         */
        dwError = LwAllocateString(
                    "_DISABLE_LSASS_NSS_ENUMERATION=1",
                    &pDisableLsassEnum);
        BAIL_ON_UMN_ERROR(dwError);
        putenv(pDisableLsassEnum);
    }

    setpwent();
    setgrent();

    while((pUser = getpwent()) != NULL)
    {
        uid = pUser->pw_uid;

        dwError = LsaFindObjects(
                    hLsass,
                    NULL,
                    0,
                    LSA_OBJECT_TYPE_USER,
                    LSA_QUERY_TYPE_BY_UNIX_ID,
                    1,
                    list,
                    &ppObjects);
        BAIL_ON_UMN_ERROR(dwError);

        if (ppObjects[0] &&
                ppObjects[0]->enabled &&
                !strcmp(ppObjects[0]->userInfo.pszUnixName, pUser->pw_name))
        {
            UMN_LOG_VERBOSE("Skipping enumerated user '%s' (uid %d) because they came from lsass",
                    pUser->pw_name, uid);
        }
        else
        {
            dwError = UmnSrvUpdateUser(hReg, hUsers, Now, pUser);
            BAIL_ON_UMN_ERROR(dwError);
        }

        LsaFreeSecurityObjectList(1, ppObjects);
        ppObjects = NULL;
    }

    while((pGroup = getgrent()) != NULL)
    {
        uid = pGroup->gr_gid;

        dwError = LsaFindObjects(
                    hLsass,
                    NULL,
                    0,
                    LSA_OBJECT_TYPE_GROUP,
                    LSA_QUERY_TYPE_BY_UNIX_ID,
                    1,
                    list,
                    &ppObjects);
        BAIL_ON_UMN_ERROR(dwError);

        if (ppObjects[0] &&
                ppObjects[0]->enabled &&
                !strcmp(ppObjects[0]->groupInfo.pszUnixName, pGroup->gr_name))
        {
            UMN_LOG_VERBOSE("Skipping enumerated group '%s' (gid %d) because they came from lsass",
                    pGroup->gr_name, uid);
        }
        else
        {
            dwError = UmnSrvUpdateGroup(hReg, hGroups, Now, pGroup);
            BAIL_ON_UMN_ERROR(dwError);
        }

        LsaFreeSecurityObjectList(1, ppObjects);
        ppObjects = NULL;
    }
    
cleanup:
    if (hLsass)
    {
        LsaCloseServer(hLsass);
    }
    if (hReg)
    {
        if (hUsers)
        {
            RegCloseKey(hReg, hUsers);
        }
        if (hGroups)
        {
            RegCloseKey(hReg, hGroups);
        }
        RegCloseServer(hReg);
    }
    if (ppObjects)
    {
        LsaFreeSecurityObjectList(1, ppObjects);
    }
    return dwError;

error:
    goto cleanup;
}

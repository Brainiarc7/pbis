/* -*- mode: c++; -*-
 *-----------------------------------------------------------------------------
 * $RCSfile: FileIDFunc.h,v $
 *
 * See Copyright for the status of this software.
 *
 * The OpenSOAP Project
 * http://opensoap.jp/
 *-----------------------------------------------------------------------------
 */

#ifndef FILE_ID_FUNC_H
#define FILE_ID_FUNC_H

/* SOAP ���b�Z�[�W�ɑΉ�����t�@�C�� ID ���擾���� */
extern
std::string
convertToFileID(const std::string& message, const std::string& spoolPath);

/* �t�@�C�� ID �ɑΉ����� SOAP ���b�Z�[�W���擾���� */
extern
std::string
revertFromFileID(const std::string& fileID, const std::string& spoolPath);

extern
int
updateFileIDContent(std::string& fileID, 
		    const std::string& message,
		    const std::string& spoolPath);

extern
int
deleteFileID(const std::string& fileID, const std::string& spoolPath);

#endif /* FILE_ID_FUNC_H */

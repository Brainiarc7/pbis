/*-----------------------------------------------------------------------------
 * $RCSfile: envelopeTst.c,v $
 *
 * See Copyright for the status of this software.
 *
 * The OpenSOAP Project
 * http://opensoap.jp/
 *-----------------------------------------------------------------------------
 */
#include <stdio.h>
#include <OpenSOAP/OpenSOAP.h>
#include <OpenSOAP/Envelope.h>
#include <OpenSOAP/Security.h>
#include "tstcmn.h"

/***************************************************************************** 
    Function      : �Í������������ۑ�
    Return        : int
 ************************************************ Yuji Yamawaki 01.11.26 *****/
static int encAndSave
(const char* szNameIn,          /* (i)  ���̓t�@�C���� */
 const char* szPubKName,        /* (i)  ���J���t�@�C���� */
 const char* szPrivKName,       /* (i)  �閧���t�@�C���� */
 const char* szNameOut)         /* (o)  �o�̓t�@�C���� */
{
    int nRet;
    OpenSOAPEnvelopePtr env = NULL;
    /* OpenSOAP API ������ */
    nRet = OpenSOAPInitialize(NULL);
    if (!OPENSOAP_SUCCEEDED(nRet)) {
        goto FuncEnd;
    }
    /* Envelope���t�@�C����胍�[�h */
    nRet = LoadEnvelope(szNameIn, &env);
    if (!OPENSOAP_SUCCEEDED(nRet)) {
        goto FuncEnd;
    }
    /* �Í��� */
    nRet = OpenSOAPSecEncWithFile(env, szPubKName);
    if (!OPENSOAP_SUCCEEDED(nRet)) {
        goto FuncEnd;
    }
    /* �����t�� */
    nRet = OpenSOAPSecAddSignWithFile(env,
                                      OPENSOAP_HA_SHA,
                                      szPrivKName,
                                      NULL);
    if (!OPENSOAP_SUCCEEDED(nRet)) {
        goto FuncEnd;
    }
    /* �Í����������̂�ۑ� */
    nRet = SaveEnvelope(env, szNameOut);
    if (!OPENSOAP_SUCCEEDED(nRet)) {
        goto FuncEnd;
    }
FuncEnd:
    OpenSOAPUltimate();
    return nRet;
}
/***************************************************************************** 
    Function      : �������؁����������ۑ�
    Return        : int
 ************************************************ Yuji Yamawaki 01.11.26 *****/
static int decAndSave
(const char* szNameIn,          /* (i)  ���̓t�@�C���� */
 const char* szPubKName,        /* (i)  ���J���t�@�C���� */
 const char* szPrivKName,       /* (i)  �閧���t�@�C���� */
 const char* szNameOut)         /* (i)  �o�̓t�@�C���� */
{
    int nRet;
    OpenSOAPEnvelopePtr env = NULL;
    /* OpenSOAP API ������ */
    nRet = OpenSOAPInitialize(NULL);
    if (!OPENSOAP_SUCCEEDED(nRet)) {
        goto FuncEnd;
    }
    /* Envelope���t�@�C����胍�[�h */
    nRet = LoadEnvelope(szNameIn, &env);
    if (!OPENSOAP_SUCCEEDED(nRet)) {
        goto FuncEnd;
    }
    /* �������� */
    nRet = OpenSOAPSecVerifySignWithFile(env,
                                         szPubKName);
    if (!OPENSOAP_SUCCEEDED(nRet)) {
        goto FuncEnd;
    }
    /* ������ */
    nRet = OpenSOAPSecDecWithFile(env, szPrivKName);
    if (!OPENSOAP_SUCCEEDED(nRet)) {
        goto FuncEnd;
    }
    /* �������������̂�ۑ� */
    nRet = SaveEnvelope(env, szNameOut);
    if (!OPENSOAP_SUCCEEDED(nRet)) {
        goto FuncEnd;
    }
FuncEnd:
    OpenSOAPUltimate();
    return nRet;
}
/***************************************************************************** 
    Function      : �g�p���@�̕\��
    Return        : void
 ************************************************ Yuji Yamawaki 01.11.26 *****/
static void usage
(const char* szProg)
{
    fprintf(stderr, "Usage: %s envName PubKeyFName PrivKeyFName\n", szProg);
}
/***************************************************************************** 
    Function      : ���C��
    Return        :int
 ************************************************ Yuji Yamawaki 01.11.26 *****/
int main(int argc, char** argv)
{
    int         nRet = 0;
    const char* szEncName = "encrypt.xml"; /* �Í������ꂽ Envelope ���� */
    /* �����̐��`�F�b�N */
    if (argc < 4) {
        usage(argv[0]);
        nRet = 1;
        goto FuncEnd;
    }
    /* �Í����e�X�g */
    nRet = encAndSave(argv[1], argv[2], argv[3], szEncName);
    if (!OPENSOAP_SUCCEEDED(nRet)) {
        fprintf(stderr, "encAndSave() Error [%08X].\n", nRet);
        nRet = -1;
        goto FuncEnd;
    }
    /* �������e�X�g */
    nRet = decAndSave(szEncName, argv[2], argv[3], "decrypt.xml");
    if (!OPENSOAP_SUCCEEDED(nRet)) {
        fprintf(stderr, "decAndSave() Error [%08X].\n", nRet);
        nRet = -1;
        goto FuncEnd;
    }
FuncEnd:
    return nRet;
}

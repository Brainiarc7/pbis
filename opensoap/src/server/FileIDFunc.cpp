/* -*- mode: c++; -*-
 *-----------------------------------------------------------------------------
 * $RCSfile: FileIDFunc.cpp,v $
 *
 * See Copyright for the status of this software.
 *
 * The OpenSOAP Project
 * http://opensoap.jp/
 *-----------------------------------------------------------------------------
 */

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unistd.h>

/* IdMgr library */
#include "ServerCommon.h"
#include "DataRetainer.h"
#include "AppLogger.h"

using namespace OpenSOAP;
using namespace std;

/* SOAP ���b�Z�[�W�ɑΉ�����t�@�C�� ID ���擾���� */
string
convertToFileID(const string& message, const string& spoolPath)
{
#ifdef DEBUG_
  AppLoggor::Write(LOG_DEBUG5,"%s=[%s]","message",message.c_str());
#endif

  string fileID;
  
  //DataRetainer �C���X�^���X����
  OpenSOAP::DataRetainer* writer = new OpenSOAP::DataRetainer(spoolPath);

  writer->Create();
  string responseFile = writer->GetHttpBodyFileName();

  //load response into SoapMessage;
  ofstream ofst(responseFile.c_str());
  ofst << message << endl;
  ofst.close();

#ifdef DEBUG_
  AppLoggor::Write(LOG_DEBUG5,"create DataFile writer finish");
#endif

  writer->GetId(fileID);

#ifdef DEBUG_
  AppLoggor::Write(LOG_DEBUG5,"%s %s=[%s]","write","id",fileID.c_str());
#endif

  delete writer;

  return fileID;
}

/* �t�@�C�� ID �ɑΉ����� SOAP ���b�Z�[�W���擾���� */
string
revertFromFileID(const string& fileID, const string& spoolPath) {

  //DataRetainer �C���X�^���X����
  OpenSOAP::DataRetainer* reader = new OpenSOAP::DataRetainer(spoolPath);

  reader->SetId(fileID);
  reader->Decompose();

  string message;
  reader->GetSoapEnvelope(message);

  delete reader;

  return message;
}

/* �t�@�C�� ID �ɑΉ����� SOAP ���b�Z�[�W�̓��e���X�V���� */
int
updateFileIDContent(string& fileID, 
                    const string& message,
                    const string& spoolPath) 
{
    int result = 0;

    if (fileID.empty()) {
        fileID = convertToFileID(message, spoolPath);
    }
    else {
        OpenSOAP::DataRetainer* dataRetainer = 
            new OpenSOAP::DataRetainer(spoolPath);

        dataRetainer->SetId(fileID);
        dataRetainer->Decompose();
        dataRetainer->UpdateSoapEnvelope(message);
        dataRetainer->Compose();
        delete dataRetainer;
    }

    return result;
}

int
deleteFileID(const string& fileID, const string& spoolPath)
{
    int result = 0;
#if 0
    string pathname = spoolPath + "/" + fileID;
    result = unlink(pathname.c_str());
#else
    DataRetainer dr(spoolPath);
    dr.SetId(fileID);
    dr.SetLifeStatus(DataRetainer::DONE);
    dr.DeleteFiles();
#endif

    return result;
}



CORBADllCalc Sample
(�ʰױ黻��CORBA�����ӥ�(DLL��)�����Ѥ���CORBA�֥�å��󥰥���ץ� )

���Υǥ��쥯�ȥ�ˤϡ�CORBADllCalc ���饤����Ȥ���ӥ����ӥ���
����ץ륳���ɤ��ޤޤ�Ƥ��ޤ�.

1.OpenSOAP API ���󥹥ȡ����ϡ�make -f CORBADllCalc.mak ��
����ѥ���Ǥ����ʲ��Υե����뤬��������ޤ�.

* CORBADllCalcClient
  CORBADllCalc ���饤����ȥץ����Ǥ�.
 
* CORBADllCalcService
  ɸ�������Ϥ��Ѥ���CORBADllCalc �����ӥ��ץ����Ǥ���inetd ���Ѥ��뤳�Ȥǡ�
  socket type �Υ����ӥ��ˤ��뤳�Ȥ���ǽ�Ǥ�.

* CORBADllCalcService.cgi
  CGI ���� CORBADllCalc �����ӥ��ץ����Ǥ�. cgi �¹Բ�ǽ�ʥǥ��쥯�ȥ�˥��ԡ�
  ���뤳�Ȥ����Ѳ�ǽ�Ȥʤ�ޤ�.

2. ����ץ�μ¹Ԥλ���:

## Test Service Programs

stest:
	cat ../RequestMessage/request_add.xml | ./CORBADllCalcService.cgi

## Test Client-Service (or Client-Server-Service) Hookups

ctest:
	./CORBADllCalcClient -s http://localhost/cgi-bin/CORBADllCalcService.cgi 12.9 + 10.0 
	
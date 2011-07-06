�uOpenSOAP Server �̓���菇�v

(0) OpenSOAP Server �̎��s�ɂ� http �T�[�o�[���K�v�ł��B
���݂� apache httpd �œ�����m�F���Ă��܂��B

(1) INSTALL.ujis �ɏ]���A�r���h�ƃC���X�g�[�����s���B
apache httpd �� OpenSOAP Server ���Ȃ�
soapInterface.cgi �̃C���X�g�[�������f�B���N�g���ɒ��ӂ��Ă��������B
�f�t�H���g�ł� /home/httpd/cgi-bin �Ȃ̂ŁA�K�v�ɉ�����
--with-cgi-bin �� CGI �����s�\�ȃf�B���N�g�����w�肵�Ă��������B

(2) �W���ł̓T�[�r�X�͕W�����o�͂ɂ��ڑ��𗘗p���܂����ASSML�̐ݒ�ɂ��
�\�P�b�g�ɂ��ڑ����\�ł��B���̏ꍇ�́ARegistService.sjis.txt �ɏ]���A
�T�[�r�X�� inetd (xinetd) �ɓo�^����K�v������܂��B
�T�[�r�X�v���O������ root �����Ŏ��s����ƃG���[�ɂȂ邱�Ƃ��A
�ȑO�񍐂���Ă��܂��B

����ɁASSML�̐ݒ�ɂ��HTTP�𗘗p�����G���h�|�C���g�̎w��ɂ��T�[�r�X
�ڑ����T�|�[�g���܂����BSSML_Readme.sjis.txt���Q�Ƃ��Ă��������B

(3) /usr/local/opensoap/etc/ �ȉ��ɂ���
�T�[�o�[�̐ݒ�t�@�C�� server.conf ��ҏW����B

* �e�T�[�o�v���Z�X�̃��O�t�@�C���̏o�͐�̐ݒ�
  <log>
    <path>/usr/local/opensoap/var/log/</path>
  </log>

* �T�[�o�v���Z�X�������Ǘ�����SOAP���b�Z�[�W�̕ێ��ꏊ�̐ݒ�
  <spool>
    <soap_message>
      <path>/usr/local/opensoap/var/spool/</path>
    </soap_message>

* �T�[�o�v���Z�X�������Ǘ�����񓯊����b�Z�[�W�Ǘ��e�[�u���̕ێ��ꏊ�̐ݒ�
    <async_table>
      <path>/usr/local/opensoap/var/spool/</path>
    </async_table>
  </spool>

* �e�T�[�o�v���Z�X�̃v���Z�XID�Ǘ��ꏊ�̐ݒ�
  <run>
    <pid>
      <path>/usr/local/opensoap/var/run/</path>
    </pid>

* �e�T�[�o�v���Z�X�̃\�P�b�g�Ǘ��ꏊ�̐ݒ�
    <socket>
      <path>/usr/local/opensoap/var/run/</path>
    </socket>
  </run>

* �T�[�o���������F�ؗp�Z�L�����e�B�L�[�̊Ǘ��ꏊ�̐ݒ�
  <security>
    <keys>
      <path>/usr/local/opensoap/etc/</path>
    </keys>
  </security>

* �T�[�r�X�Ǘ��pSSML�t�@�C���̓o�^��̐ݒ�
  <ssml>
    <path>/usr/local/opensoap/etc/ssml/</path>
  </ssml>

* �񓯊��]�����̕ԑ����b�Z�[�W���ԐM�����EndPoint�̐ݒ�
  �����Ŏw�肵��EndPoint�ɑ΂��ē]���悩��ԐM���b�Z�[�W�������邽�߁A
  �]���悩��Q�Ƃł��鎩�T�[�o�̏��ł���K�v������B
  �܂��A���b�Z�[�W�]���̃��[�v���`�F�b�N���邽�߂ɁA���g�̕ʖ���IP�������
  �������Q�ڈȍ~��<url>�Ƃ��ċL�q���Ă����B

  �ȉ��̗�̏ꍇ�́A"http://myhost.opensoap.jp/cgi-bin/soapInterface.cgi"
  �ɑ΂��ĕԐM�����B

  <backward>
    <url>http://myhost.opensoap.jp/cgi-bin/soapInterface.cgi</url>
    <url>http://192.168.0.123/cgi-bin/soapInterface.cgi</url>
    <url>http://soap-server.opensoap.jp/cgi-bin/soapInterface.cgi</url>
  </backward>

* ���T�[�o�Ǘ����ɑΏۃT�[�r�X�������ꍇ�ɁA���b�Z�[�W���]�������
  �T�[�o��EndPoint��<url>�ɐݒ肷��B

  �ȉ��̗�̏ꍇ�́A"http://yourhost.opensoap.jp/cgi-bin/soapInterface.cgi"
  �ɑ΂��ē]�������B

  <forwarder>
    <url>http://yourhost.opensoap.jp/cgi-bin/soapInterface.cgi</url>
  </forwarder>

* �񓯊����b�Z�[�W��ID�ȂǁA�T�[�o�����䂷�郁�b�Z�[�W�ɑ΂���
  �T�[�o�̏�����t�����邩�ۂ��̐ݒ�
  �T�[�o�̏�����t���������ꍇ�� true ��ݒ肷��B

  <add_signature>false</add_signature>

* �T�[�o����t����SOAP���b�Z�[�W�̍ő�T�C�Y���w�肷��B
  �P�ʂ�byte. 500k, 1M�Ȃǂ̎w����\�B
  -1�Ȃǂ̃}�C�i�X�̒l���w�肵���ꍇ�͐��������B
  0���w�肵���ꍇ�̓��b�Z�[�W����t���Ȃ��w��ƂȂ�B

  <limit>
    <soap_message_size>1M</soap_message_size>
  </limit>

* �񓯊������ɂ�����A�������̓����L���[�A�X�v�[���f�[�^�̔j�����Ԃ�
  �w�肷��B
  0�ȉ��̒l�͖����B
  �i���w��̏ꍇ�̓V�X�e�������f�t�H���g�l3600���g�p�����j

  <limit>
    <ttl>
      <asynchronizedTTL>3600</asynchronizedTTL>
    </ttl>
  </limit>

  �����̒l�́A�e�T�[�r�X����SSML�t�@�C���ɂ��w�肷�邱�Ƃ��\�ł���A
    SSML�t�@�C���Ɏw�肪����ꍇ�́A������̒l���D�悳���B

  ���܂��A�ʂ�SOAP���b�Z�[�W���̊g���w�b�_�ɂ����l�̒l���w��ł��邪�A
    ���̏ꍇ�́A�Ή�����SSML�ł̎w�肪����΁A���̒l�����������ꍇ�̂�
    �L���ƂȂ�BSSML�ł̎w�肪������΁Aserver.conf���̒l�����������ꍇ
    �ɗL���ƂȂ�B

        �ݒ��j                  
        server.conf | 10  10  10  10  10  10 
        SSML        | -   20   5  20  20  -
        SOAP-Header | -   -   -   30  15  15
        --------------------------------------
        �L���l      | 10  20   5  20  15  10


* ���������ɂ�����A���ꂼ���SOAP���b�Z�[�W�����^�C���A�E�g���Ԃ��w�肷��B
  0�ȉ��̒l�͖����B
  �i���w��̏ꍇ�̓V�X�e�������f�t�H���g�l600���g�p�����j

  <limit>
    <ttl>
      <synchronizedTTL>600</synchronizedTTL>
    </ttl>
  </limit>

  ��SSML�t�@�C�����̎w�肨��сASOAP���b�Z�[�W���̊g���w�b�_�ł̎w���
    �����́A��L <asynchronizedTTL>�Ɠ����B

* SOAP���b�Z�[�W�̓]���񐔂̐������w�肷��B
  0���w�肵���ꍇ�́A�]�����s��Ȃ��B
  �}�C�i�X�̒l�͖����B
  �i���w��̏ꍇ�̓V�X�e�������f�t�H���g�l4���g�p�����j

  <limit>
    <ttl>
      <hoptimes>4</hoptimes>
    </ttl>
  </limit>

  ��SSML�t�@�C�����̎w�肨��сASOAP���b�Z�[�W���̊g���w�b�_�ł̎w���
    �����́A��L <asynchronizedTTL>�Ɠ����B

* ���O�o�͂Ɋւ���ݒ�̈ꗗ���ȉ��Ɏ����B

  <Logging><System><LogType>
	���O�̎�ށBsyslog=syslog�ւ̏o�́Bfile=�t�@�C���ւ̏o�́B
	�f�t�H���g�l��syslog

  <Logging><System><LogFormat>
	�o�͓��e�Bgeneric=�T���o�́Bdetail=�ڍ׏o�́B
	�f�t�H���g�l��generic

  <Logging><System><Option>
	LogType=syslog�̏ꍇ�̃I�v�V�����w��Bsyslog�ւ̈������w�肷��B
	�K�v�ȃI�v�V�����l�𑫂����l��ݒ�B

	1=PID:		�v���Z�XID��\������
	2=CONSOLE:	�R���\�[���֏o�͂���
	4=ODELAY:	���O�̏���������syslog�Ɛڑ�����
	8=NDELAY:	���O�̏��񏑂����ݎ���syslog�Ɛڑ�����
	16=NOWAIT:	syslog�ւ̏������ݎ��Ɏq�v���Z�X�I����҂����ɏI��
	32=PERROR:	stderr�ɂ������ɏo�͂���

	�f�t�H���g�l��5(=1+4)

  <Logging><System><Facility>
	LogType=syslog�̏ꍇ�̃I�v�V�����w��Bsyslog�t�@�V���e�B�[�̐ݒ�B

	0=KERN
	8=USER
	24=DAEMON
	128=LOCAL0
	136=LOCAL1
	144=LOCAL2

	�f�t�H���g�l��8
	
  <Logging><System><DefaultOutputLevel>
	LogType=syslog�p�I�v�V�����B�ڑ����̂݁B
	����������g�p�B����J���p�̂��߁A�ύX�s�B

  <Logging><System><LogLevel>
	���ʃI�v�V�����B���O�o�͂̃��x���ݒ�B�w��ȏ�̃��b�Z�[�W�̂ݏo�́B

	0=EMERG:	�[���ȃG���[
	2=ALERT:	�A���[�g���x���̃G���[
	3=ERR:		�G���[
	4=WARN:		�x�����x���̃G���[
	5=NOTICE:	���Ӄ��x���̃G���[
	6=INFO:		���
	7-16=DEBUG:	�ǉ��ߑ����x���i�f�o�b�O�j

	�f�t�H���g�l��6

  <Logging><Application><LogType>
	<Logging><System><LogType>�Ɠ����B
	�f�t�H���g�l��file

  <Logging><Application><LogFormat>
	<Logging><System><LogFormat>�Ɠ����B
	�f�t�H���g�l��detail

  <Logging><Application><FileName>
	LogType=file�p�I�v�V�����B
	���O�t�@�C�����i���S�p�X�w��j���w�肷��B

  <Logging><Application><LogLevel>
	<Logging><System><LogLevel>�Ɠ����B

  ���ȉ���<�v���Z�X��>���w�肷�邱�Ƃɂ��A�v���Z�X�ʂɃ��O�t�@�C���𕪂���
    ���Ƃ��\�ƂȂ�B�ݒ荀�ڂ�<Logging><Application>�Ɠ���
  <Logging><�v���Z�X��>
	

(4) /usr/local/opensoap/etc/ssml/ �ȉ���
�T�[�r�X�ݒ�t�@�C�� SSML �t�@�C����u���B(server.conf�ł̏����ݒ�̏ꍇ)
SSML �̋L�q�@�ɕt���Ă͓��f�B���N�g���ȉ��ɂ���
SSML_Readme.txt ���Q�Ƃ��邱�ƁB

(5) apache httpd ���N�����Ă��邱�Ƃ��m�F����B
�N�����Ă��Ȃ��ꍇ�͋N�����s���B

(6) �T�[�o�[�v���Z�X�̊J�n�B
${sbindir} (�f�t�H���g�ł� /usr/local/opensoap/sbin) �Ƀp�X��ʂ��B
(6-00) ${sbindir}/opensoap-server-ctl start �����s����B
��1: ��~����ۂ� ${sbindir}/opensoap-server-ctl stop �����s����B
��2: SSML ��ǉ������ۂ� ${sbindir}/opensoap-server-ctl reload �����s����B
==============
 �v���Z�X�ꗗ
==============
��3: (6-00) �ł͈ȉ��� (6-01)�`(6-9) �����s�����B
(6-01) OpenSOAPMgr
       - �ȉ��̊e�T�[�o�v���Z�X���Ǘ��i���s��~���j����}�l�[�W���v���Z�X
(6-02) srvConfAttrMgr 
         - �T�[�o�ݒ���Ǘ��@�\�v���Z�X
(6-03) ssmlAttrMgr 
         - SSML���Ǘ��@�\�v���Z�X
(6-04) idManager
         - ���b�Z�[�W�����Ǘ����ʎq���s�@�\�v���Z�X
(6-05) msgDrvCreator
         - ���b�Z�[�W�����U�蕪���@�\�v���Z�X
(6-06) queueManager
         - ���b�Z�[�W�L���[�Ǘ��@�\�v���Z�X
(6-07) queueManager 1 
         - �]���p���b�Z�[�W�L���[�Ǘ��@�\�v���Z�X
(6-08) spoolManager
         - �񓯊����X�|���X���b�Z�[�W�X�v�[���@�\�v���Z�X
(6-09) ttlManager
         - ���b�Z�[�W�ێ����ԊǗ��@�\�v���Z�X

��4: �s���ɃT�[�o�v���Z�X���c���Ă��܂����ꍇ�́A��L�v���Z�X��������
    �v���Z�X���I�������Ă��������B


(7) �N���C�A���g�v���O���������s����B

��������������������������������������
�uOpenSOAP �T�[�o�[�̃f�o�b�O�E�o�O�̕񍐁v

(1) /usr/local/opensoap/var/log/ �ȉ���
�e�v���O�����̃��O�������o�����̂ŁA
�ǂ��ŃG���[�ɂȂ��Ă��邩�`�F�b�N���Ă��������B(server.conf�����ݒ莞)

(2) configure �̃I�v�V������ CXXFLAGS=-DDEBUG ��t�����
�ڍׂȃ��O���o�܂��B

(3) �s���I�����Ă��܂����v���O������
opensoap-server-ctl stop �̍ۂɖ��O���\������܂���B
�G���[�񍐂̍ۂɋ����Ă���������Ə�����܂��B

SSML�T���v������iSample.ssml)

<?xml version='1.0' encoding='UTF-8' ?>
<SSML xmlns="x-schema:ssmlSchema.xml">

SSML(Soap Service Markup Language)�̍ŏ�ʗv�f��<SSML>�ł���C�T�[�r�X����
��`����<service>�v�f���ЂƂ܂݂܂��D
SSML�t�@�C�����͕֋X�I�ɂ��̃T�[�r�X���Ɠ���ɂ��܂��D

<service name='Sample' nsuri='http://services.opensoap.jp/samples/Sample/'>

<service>�m�[�h�ɂ͂ЂƂȏ��<connection>�v�f�ƁC�C�ӂ̐���<operation>�v�f�C
�ЂƂ�<fault>�v�f�C�ЂƂȉ���<MaxProccessNumber>�v�f���܂݂܂��D
�T�[�o���ŃI�y���[�V���������d������ȂǁC�K�v�ȏꍇ�ɂ�<service>�m�[�h��
�܂܂��nsuri�����ŃT�[�r�X�̖��O��Ԃ��w�肵�܂��D

<connection name='Sample1'>
	<Socket hostname='localhost' port='8765'/>
	<asynchronizedTTL>8000</asynchronizedTTL>
	<synchronizedTTL count="second">20</synchronizedTTL>
	<MaxProccessNumber>5</MaxProccessNumber>
</connection>
<connection name='Sample2'>
        <StdIO>
                <exec prog='/usr/local/sbin/SampleService' option='-s -u'/>
	</StdIO>
	<asynchronizedTTL>8000</asynchronizedTTL>
	<synchronizedTTL count="second">20</synchronizedTTL>
	<MaxProccessNumber>5</MaxProccessNumber>
</connection>

<connection name='Sample3'>
	<HTTP>
	  <url>http://services.opensoap.jp/cgi-bin/TargetService.cgi</url>
	</HTTP>
	<asynchronizedTTL>8000</asynchronizedTTL>
	<synchronizedTTL count="second">20</synchronizedTTL>
	<MaxProccessNumber>5</MaxProccessNumber>
</connection>

<connection>�v�f�ł́C�T�[�r�X�Ƃ̐ڑ����@���L�q���܂��D�ڑ����@�ɂ�

�Esocket:
	<Socket hostname='�T�[�r�X�v���O�����̂���z�X�g��' port='�|�[�g�ԍ�'/>
	�iinetd��������xinetd�ւ̓o�^���K�v�ł��D�Q�ƁFRegistService.ujis�j

�E�W�����o��:
	<StdIO>�̎q�v�f<exec prog='�W�����o�͂ŉғ�����T�[�r�X�v���O�����{�̂�
	�p�X' option='�v���O�����ɓn���R�}���h���C������'/>

�EHTTP:
	<connection>�̎q�v�f�Ƃ���<url>���w�肵�܂��B
	<url>�ɂ́A�ďo�ΏۃT�[�r�X�̃G���h�|�C���g���w�肵�܂��B

�E���O���p�C�v:<FIFO>�i�������j
�EIPC:<IPC>�i�������j
�ECOM:<COM>�i�������j
�E���̑��ڑ����W���[��:<Module>�i�������j
���w�肷�邱�Ƃ��ł��܂��D

����ɁC�񓯊��v���Z�X�ł̃^�C���A�E�g����(���������̃L���[�A�X�v�[����
�f�[�^���j������鎞��)(�b)<asynchronizedTTL>�C
�����v���Z�X�ł̃^�C���A�E�g����<synchronizedTTL>�icount�����ŕb'second'�C
�܂��̓��b�Z�[�W�̃z�b�v��'hoptimes'���w��ł��܂��D�j���w�肵�܂��D
�����͓����Ɏw�肷�邱�Ƃ��ł��C���N�G�X�g���b�Z�[�W�ɂ�铯���E�񓯊���
�w��ɂ���Ďg���������܂��D
  �z�b�v��'hoptimes'�ł̎w��́A�ΏۃT�[�r�X�ďo���ɁA���Y�T�[�o�ւ̓]��
�񐔂��`�F�b�N��(received_path�̐����`�F�b�N����)�A�w��hoptimes���]��
�񐔂̕����傫����΁A�T�[�r�X�ďo��������Fault�𔭐�����B


�����l�̒l�Ƃ��āAserver.conf���Ɉȉ��̐ݒ肪�ł��܂��B
  �l�̈����Ƃ��āASSML���ŗL���Ȓl�̎w��(0���傫���l�B�������Ahoptimes��0��
  �w�肷��Ɠ]�����Ȃ��w��)������΁Aserver.conf�̒l���D�悵�Ďg�p����܂�
  (�l�̑召�ɂ�炸)�B

-- in server.conf
  <limit>
    <ttl>
      <asynchronizedTTL>3600</asynchronizedTTL>
      <synchronizedTTL>600</synchronizedTTL>
      <hoptimes>4</hoptimes>
  </limit>
--
	
<MaxProccessNumber>�ŁC���̐ڑ����@�ɂ��ő�ڑ������w��ł��܂��D

<operation type ='Sample1'>add</operation>
<operation type ='Sample2'>sub</operation>

<operation>�v�f�ł́C<connection>��name�����Ŏw�肵���ڑ����@���w�肵��
�I�y���[�V���������L�q���܂��D
�ЂƂ̃T�[�r�X�ɐڑ��@�̈قȂ镡���̃I�y���[�V�����������Ă����܂��܂���D

<fault signature='1' />

<fault>�v�f�ł̓T�[�o���Ԃ�Fault���b�Z�[�W�ɃT�[�o�̏�����t�����邩�ǂ�����
signature����('0' or '1')�Ŏw�肵�܂��D

<MaxProccessNumber>15</MaxProccessNumber>

<MaxProccessNumber>�ŃT�[�r�X�S�̂̃v���Z�X�N�����𐧌��ł��܂��D

------
LastModified: Aug, 31. 2003


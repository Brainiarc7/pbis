OpenSOAP$B%5!<%P$N(BApache DSO$B%b%8%e!<%k$K$D$$$F(B
============================================

OpenSOAP$B%5!<%P$G$O!"(BHTTP$B%H%i%s%9%]!<%H$N<u?.%$%s%?!<%U%'%$%9$H$7$F!"(B
Apache$B$N(BCGI$B$r;H$C$F8F$S=P$5$l$^$9!#(B
$B%a%C%;!<%8$N%H%i%s%6%/%7%g%s$,A}Bg$9$k$H!"$3$N8F$S=P$7ItJ,$,%*!<%P!<%X%C(B
$B%I$H$J$j=hM}G=NO$,Dc2<$9$k$?$a!"(Bapache$B$N(BDSO(Dynamic Shared Object)$B$KBP(B
$B1~$5$;$^$7$?!#$3$l$K$h$j!"(B20%$BDxEY$N@-G=$N8~>e$,$"$j$^$7$?!#(B

$B$^$?!"=>Mh07$($J$+$C$?!"E:IU%G!<%?$r4^$`%a%C%;!<%8$r07$&$3$H$,$G$-$k$h(B
$B$&$K$J$C$F$$$^$9!#(B
WS-Attachments $B5Z$S(B SOAP with Attachments(SwA)$B$K=`5r$7$?(B DIME / MIME
$BJ}<0$NE:IU%a%C%;!<%8$NE>Aw$,2DG=$K$J$j$^$7$?!#(B

$B$3$N%b%8%e!<%k5!G=$r;H$&$?$a$K$O!"(BApache2$B$N(BDSO$B%b%8%e!<%k$rMxMQ$G$-$k4D(B
$B6-$H!"(Bhttpd.conf$BFb$G$NDI2C@_Dj$,I,MW$H$J$j$^$9!#(B

--------------
$B%3%s%Q%$%kJ}K!(B
--------------
$B$^$:!"%=!<%9%3!<%I$+$i$N%3%s%Q%$%k$N$?$a$K$O(B httpd-devel$BAjEv$N%Q%C%1!<(B
$B%8$,%$%s%9%H!<%k$5$l$F$$$kI,MW$,$"$j!"(Bapxs (APache eXtenSion tool)$B%3%^(B
$B%s%I$,@5$7$/<B9T$G$-$kI,MW$,$"$j$^$9!#(B
$B$3$l$i$,B7$C$F$$$l$P!"(Bconfigure$B$G<+F0G'<1$5$l$^$9!#%3%s%Q%$%k$N>\:Y$O!"(B
INSTALL$B%I%-%e%a%s%H$r$4Mw2<$5$$!#(B

$B@5$7$/(Bmake$B$,40N;$7$?>l9g$K$O!":n@.$5$l$k%b%8%e!<%k%U%!%$%kL>$O(B
mod_opensoap.so $B$H$J$j!"(B /usr/lib/httpd/modules/ (RedHat9$B$N>l9g(B)
$B$J$I$K%$%s%9%H!<%k$5$l$^$9!#(B

--------
$B@_DjJ}K!(B
--------
mod_opensoap$B5!G=$rM-8z$K$9$k$?$a$K(B httpd.conf $BFb$K0J2<$N5-=R$rDI2C$7$^(B
$B$9!#(B

  #####The following lines need to be included in Apache2 httpd.conf
  #####for OpenSOAP Server DSO
  LoadFile /usr/local/opensoap/lib/libOpenSOAPServer.so
  LoadFile /usr/local/opensoap/lib/libOpenSOAPInterface.so
  LoadModule opensoap_module modules/mod_opensoap.so
  <Location /opensoap>
  SetHandler opensoap
  </Location>

LoadFile$B$K5-=R$9$k9T$O!"%$%s%9%H!<%k$5$l$k(BOpenSOAP$B%5!<%PMQ$N%i%$%V%i%j(B
$B%U%!%$%kL>$G!"%$%s%9%H!<%k<j=g$K$h$j0J2<$N$h$&$K0[$J$k2DG=@-$,$"$j$^$9!#(B
  /usr/local/opensoap/lib/libOpenSOAPServer.so
  /usr/lib/libOpenSOAPServer.so

$B$^$?!"(BRedHat7.3$BEy$G$O(B libstdc++$B%i%$%V%i%j$X$N%Q%9L>$,I,MW$H$J$k>l9g$,(B
$B$"$j$^$9!#(B
  # (libstdc++ is only for RedHat7.3)
  LoadFile /usr/lib/libstdc++-3-libc6.2-2-2.10.0.so

$B%b%8%e!<%k5!G=$rM-8z$9$k$?$a$K!"(BOpenSOAP$B%5!<%P$H$H$b$K(Bhttpd$B%5!<%S%9$r(B
$B:F5/F0$7$F2<$5$$!#(B

$BNc(B:
  # /etc/init.d/httpd restart
  # /etc/init.d/opensoap restart
 ($B$"$k$$$O!"(B)
  # apachectl restart
  # opensoap-server-ctl restart

------------------
$B%"%/%;%9!&3NG'J}K!(B
------------------
DSO$B%b%8%e!<%k7PM3$G%"%/%;%9$9$k>l9g$O!"%(%s%I%]%$%s%H$,!"(B
soapInterface.cgi $B$G$O$J$/!"(Bhttp://$B%[%9%HL>(B/opensoap $B$KBX$o$j$^$9!#(B

  $ soaping http://localhost/opensoap
  SOAPING http://localhost/opensoap : 0 byte string.
  soaping-seq=0 time=14.619 msec
 
  --- http://localhost/opensoap soaping statistics ---
  1 messages transmitted, 1 received, 0% loss, time 14.619ms
  Round-Trip min/avg/max/mdev = 14.619/14.619/14.619/0.000 msec

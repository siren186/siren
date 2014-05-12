#! /bin/csh -f
# This software may only be used by you under license from the
# University of Notre Dame.  A copy of the University of Notre Dame's
# Source Code Agreement is available at the inilib Internet website
# having the URL: <http://inilib.sourceforge.net/license/> If you
# received this software without first entering into a license with the
# University of Notre Dame, you have an infringing copy of this software
# and cannot use it without violating the University of Notre Dame's
# intellectual property rights.
#

set VERSIONFILE=VERSION

set start=`date`
cat <<EOF
 
Creating inilib distribution
In directory: `pwd`
Started: $start
 
EOF

umask 022
set p="`pwd`"

#########################################################
# VERY IMPORTANT: Now go into the new distribution tree #
#########################################################

cd $distdir

set ver="`cat VERSION`"

#
# Put in those headers
#
 
echo "*** Inserting license headers..."

set filelist=/tmp/inilib-license-filelist.$$
rm -f $filelist
cat > $filelist <<EOF
INSTALL
LICENSE
NEWS
README
EOF
find config -type f -print >> $filelist
find doc -type f -print >> $filelist
find src -type f -print >> $filelist

chmod +x ./config/insertlic.csh 
./config/insertlic.csh $filelist
rm -rf $filelist

#
# Put the release version number in the README & INSTALL.  NEWS is
# already checked to match with latest version number by Automake #
#

echo "*** Updating version number in README & INSTALL..."
foreach file (README INSTALL)
    echo " - Setting $file"
    if (-f $file) then
	sed -e "s/INILIBRV/$ver/" $file > bar
	mv -f bar $file
    endif
end

#
# make the docs...
#
set nowpwd=`pwd`
cd $p/doc
set docdir=/tmp/inilib-doc.$$
rm -rf $docdir
mkdir $docdir
make squeaky pdf
cp inilib.pdf $docdir/.
make squeaky ps
cp inilib.ps $docdir/.
make squeaky
cp $docdir/* $nowpwd/doc/.
rm -rf $docdir
cd $nowpwd

#
# Set social Unix perms
#
 
echo "*** Setting social Unix permissions..."
chmod +x 	config/config.guess config/config.sub \
	config/install-sh \
	config/missing config/mkinstalldirs

cat <<EOF
*** inlib version $ver distribution created
 
Started: $start
Ended:   `date`
 
EOF


#!/bin/sh

git clone git://git.eukrea.fr/eukrea-oe/setup-scripts.git openembedded -b eukrea-denzil
cd openembedded
./oebb.sh config eukrea-cpuimx51
source .oe/environment-oecore
bitbake -c fetch eukrea-base-image
sed -i 's/INHERIT += "rm_work"/#INHERIT += "rm_work"/g' conf/local.conf
bitbake eukrea-base-image

exit 0

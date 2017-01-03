#/bin/bash

for file in `ls *.gdml`; do
    perl -p -i -e 's/<!ENTITY gwd >/<!ENTITY gwd \"$ENV{'PWD'}\/\">/g' ${file}
done
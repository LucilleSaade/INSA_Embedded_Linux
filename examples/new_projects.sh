#!/bin/bash
WORKSET=~/workset
echo "Nom du projet"
read PNAME
echo "Creation des fichiers de développement"
mkdir -p $WORKSET/$PNAME
cd $WORKSET/$PNAME
mkdir -p src
touch README
# Creating main source file
echo "#include <stdio.h>
#include <stdlib.h>
int main ( int argc, char ** argv )
{
printf(\"Start of ${PNAME} project!!!\n\");
return EXIT_SUCCESS;
}" > src/${PNAME}.c
# Creating Makefile.ams
echo "
bin_PROGRAMS = ${PNAME}
${PNAME}_SOURCES = ${PNAME}.c
" > src/Makefile.am
echo '
SUBDIRS = src
dist_doc_DATA = README
' > Makefile.am
# Creating configure.ac
echo "
AC_INIT([${PNAME}], [1.0], [fabienlahoudere.pro@gmail.com])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_PROG_CC
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
Makefile
src/Makefile
])
AC_OUTPUT
" > configure.ac
tree
# Initialize git project and perform first commit
git init
git add Makefile.am configure.ac src/Makefile.am src/${PNAME}.c README
git commit -m "Initial commit of project ${PNAME}"
#autoreconf --install

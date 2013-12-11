#! /bin/bash
#=============================================================================
#       FileName :          GenerateDictionary.sh
#       Version  :          0.0.1
#       Author   :          Chi WANG    (chiwang@mail.ustc.edu.cn)
#       Time     :          2013-12-11   16:15:20
#------------------------------------------------------------------------------
#       Description  :
#   Using rootcint
#       http://www.scons.org/doc/HTML/scons-user.html#chap-builders-writing
#       http://kalmanalignment.hepforge.org/svn/trunk/event/SConscript
#   Requirement
#       1.  must has 2 directories (include, src) at where you execute this script
#
#   Usage:
#       1.  0 arguments
#           find *LinkDef* in include; use all header files in include
#       2.  at least 2 arguments (LinkDef, header files)
#           use *LinkDef*;  use header files
#
#------------------------------------------------------------------------------
#       History  :
#                                          Update:  2013-12-11   21:52:53
#=============================================================================

includeDir="./include"
srcDir="./src"

if [ ! -d $includeDir ];then
    echo "Error:    do NOT have include directory: $includeDir..."
    exit 0
fi
if [ ! -d $srcDir ];then
    echo "Error:    do NOT have src directory: $srcDir..."
fi


if [ $# = 0 ];then
#+  $# = 0
#   use LinkDef.h in $includeDir, all the other header files as fileList
nLinkDef=0
for file in `ls $includeDir`;do
    if [[ $file =~ "LinkDef" && $file =~ ".h" ]];then
        linkDef=$file
        let nLinkDef=$nLinkDef+1
    else
        fileList="$fileList $file"
    fi
    if [ $nLinkDef = "2" ];then
        echo "Error:    there're $nLinkDef LinkDef.h files..."
        echo "must declare one LinkDef.h file and some header file as command arguments.."
        exit 0
    fi
done

else
#+  $# != 0
#   must input at least 2 arguments:
#   1st:    WhichLinkDef.h
#   2nd ~ $#:   header file list ()

while [ $# != 0 ];do
    if [[ $1 =~ "LinkDef" && $1 =~ ".h" ]];then
        linkDef=$1
    else
        fileList="$fileList $1"
    fi
    shift
done

fi

diction=`echo $linkDef | sed s/LinkDef//`
diction="${diction%.*}_Dict.cc"

if [ -f $srcDir/$diction ];then
    read -p   " dictionary ($diction) is exist, delete it? (Y/N):        " Ans
    if [ $Ans == "Y" ];then
        \rm ./*/${diction%.*}* 2>/dev/null
        echo "You should to re-execute this command."
    fi
    exit 0      # can't execute rootcint just after \rm ....
fi

echo "generating    $diction"
rootcint -f ${includeDir}/${diction} -c -p -I$includeDir $fileList $linkDef
mv $includeDir/$diction $srcDir/$diction 2>/dev/null


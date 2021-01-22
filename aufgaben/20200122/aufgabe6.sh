#! /bin/bash
while [[ $# -gt 0 ]]
do
    key="$1"
    case $key in
        -c|--compile)
            compile=1
            shift
            ;;
        -r|--run)
            run=1
            shift
            ;;
        -a|--all)
            compile=1
            run=1
            shift
            ;;
    esac
done

if [[ -z "$run"  && -z "$compile" ]]; then
    echo 'No flags given, running with both -r (run) and -c (compile).'
    run=1
    compile=1
fi

if [[ -v compile ]]; then
    echo 'Generating dictionary'
    rootcling -f src/FourVectorDict.cxx -I include -rmf lib/libFourVector.rootmap -c FourVector.h LinkDef.h

    echo 'Creating shared library'
    gcc -shared \
        -o lib/libFourVector.so \
        `root-config --cflags --ldflags --glibs` \
        -I include \
        -fPIC -O3 src/FourVectorDict.cxx src/FourVector.cxx
fi

if [[ -v run ]]; then
    echo 'Running write file'
    root \
        -q \
        -L $PWD/lib/libFourVector.so \
        -x $PWD/src/write_data.c \
        -I $PWD/include
    echo 'Running read file'
    root \
        -q \
        -L $PWD/lib/libFourVector.so \
        -x $PWD/src/read_data.c \
        -I $PWD/include
fi

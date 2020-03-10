# jPython
Sample project for calling Python from jBASE 5

## Introduction
This is a demo project to demonstrate how to call Python routines from jBASE.
It was written/built against Python 3.6 (though other versions may also work).

The project builds a shared library (**libjpython**) and a test program (**callpython_test**).

## Requirements
jBASE 5 >

Python 3.x (tested with 3.6m)

## Building

### Linux
```
make
```

If you wish to build against a specific maj.min release of Python (e.g. 3.7):

```
make pythonMaj=3 pythonMin=7
```

## Running the Sample
Build the shared library (see Building)

Point your JBCOBJECTLIST to the location of the shared lib.
>Alternatively **sudo cp lib/\* $JBCRELEASEDIR/lib**
```
export JBCOBJECTLIST=`pwd`/lib:$JBCOBJECTLIST
```
Depending on your set up you may need to point LD_LIBRARY_PATH to the location of Python's shared library.

>The following is specific to the version of Python installed:
```
export LD_LIBRARY_PATH=/opt/rh/rh-python36/root/usr/lib64:$JBCRELEASEDIR/lib
```
Now you should be able to run:

```
bin/callpython_test 45.4157 122.7163 33.9890 151.1393
Distance between 45.4157/122.7163 and 33.9890/151.1393 is 2726.361341
```

## Notes on the jabba syntax
The examples were written prior to the **JVAR** macro (which makes the
language transition between C and jBC vars relatively painless).

Instead the **\#VARAPPEND** directive is used throughout.

Future updates will be targeted to 5.7.6> using **JVAR**.

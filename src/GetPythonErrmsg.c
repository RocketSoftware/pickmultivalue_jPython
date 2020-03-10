/*--
GetPythonErrorMessage

Assuming a Python error has occurred in the current thread state,
return a "char *" which is a formatted traceback, or NULL if the
traceback can not be obtained.

If a non-NULL value is returned, it should be passed to "free()" when
it is no longer needed (the string is allocated using strdup!)

Uses the built-in library modules cStringIO and traceback, so if the
core Python library is not setup correctly, this will not work.

Regardless of if the function succeeds, the exception state id
always restored to how it was when we were entered.  The caller
may still wish to call PyErr_Clear() to clean it all up.

Mark Hammond - Jan 1998
--*/
#define GPEM_ERROR(what) {errorMsg = "<Error getting traceback - " ##
what ## ">";goto done;}

char *GetPythonErrorMessage()
{
	char *result = NULL;
	char *errorMsg = NULL;
	PyObject *modStringIO = NULL;
	PyObject *modTB = NULL;
	PyObject *obFuncStringIO = NULL;
	PyObject *obStringIO = NULL;
	PyObject *obFuncTB = NULL;
	PyObject *argsTB = NULL;
	PyObject *obResult = NULL;
	PyObject *exc_typ, *exc_val, *exc_tb;
	/* Fetch the error state now before we cruch it */
	PyErr_Fetch(&exc_typ, &exc_val, &exc_tb);

	/* Import the modules we need - cStringIO and traceback */
	modStringIO = PyImport_ImportModule("cStringIO");
	if (modStringIO == NULL)
		GPEM_ERROR("cant import cStringIO");
	modTB = PyImport_ImportModule("traceback");
	if (modTB == NULL)
		GPEM_ERROR("cant import traceback");

	/* Construct a cStringIO object */
	obFuncStringIO = PyObject_GetAttrString(modStringIO, "StringIO");
	if (obFuncStringIO == NULL)
		GPEM_ERROR("cant find cStringIO.StringIO");
	obStringIO = PyObject_CallObject(obFuncStringIO, NULL);
	if (obStringIO == NULL)
		GPEM_ERROR("cStringIO.StringIO() failed");

	/* Get the traceback.print_exception function, and call it. */
	obFuncTB = PyObject_GetAttrString(modTB, "print_exception");
	if (obFuncTB == NULL)
		GPEM_ERROR("cant find traceback.print_exception");
	argsTB = Py_BuildValue("OOOOO",
						   exc_typ ? exc_typ : Py_None,
						   exc_val ? exc_val : Py_None,
						   exc_tb ? exc_tb : Py_None,
						   Py_None,
						   obStringIO);
	if (argsTB == NULL)
		GPEM_ERROR("cant make print_exception arguments");

	obResult = PyObject_CallObject(obFuncTB, argsTB);
	if (obResult == NULL)
		GPEM_ERROR("traceback.print_exception() failed");

	/* Now call the getvalue() method in the StringIO instance */
	Py_DECREF(obFuncStringIO);
	obFuncStringIO = PyObject_GetAttrString(obStringIO, "getvalue");
	if (obFuncStringIO == NULL)
		GPEM_ERROR("cant find getvalue function");
	Py_DECREF(obResult);
	obResult = PyObject_CallObject(obFuncStringIO, NULL);
	if (obResult == NULL)
		GPEM_ERROR("getvalue() failed.");

	/* And it should be a string all ready to go - duplicate it. */
	if (!PyString_Check(obResult))
		GPEM_ERROR("getvalue() did not return a string");
	result = strdup(PyString_AsString(obResult));
done:
	if (result == NULL && errorMsg != NULL)
		result = strdup(errorMsg);
	Py_XDECREF(modStringIO);
	Py_XDECREF(modTB);
	Py_XDECREF(obFuncStringIO);
	Py_XDECREF(obStringIO);
	Py_XDECREF(obFuncTB);
	Py_XDECREF(argsTB);
	Py_XDECREF(obResult);

	/* Restore the exception state */
	PyErr_Restore(exc_typ, exc_val, exc_tb);
	return result;
}

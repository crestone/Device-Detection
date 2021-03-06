<<<<<<< HEAD
/*

This Source Code Form is copyright of Yorkshire, Inc.
Copyright © 2014 Yorkshire, Inc,
Guiyang, Guizhou, China

This Source Code Form is copyright of 51Degrees Mobile Experts Limited.
Copyright © 2014 51Degrees Mobile Experts Limited, 5 Charlotte Close,
Caversham, Reading, Berkshire, United Kingdom RG4 7BY

This Source Code Form is the subject of the following patent
applications, owned by 51Degrees Mobile Experts Limited of 5 Charlotte
Close, Caversham, Reading, Berkshire, United Kingdom RG4 7BY:
European Patent Application No. 13192291.6; and
United States Patent Application Nos. 14/085,223 and 14/085,301.

This Source Code Form is subject to the terms of the Mozilla Public
License, v. 2.0.

If a copy of the MPL was not distributed with this file, You can obtain
one at http://mozilla.org/MPL/2.0/.

This Source Code Form is “Incompatible With Secondary Licenses”, as
defined by the Mozilla Public License, v. 2.0.

*/
=======
/* *********************************************************************
* This Source Code Form is copyright of 51Degrees Mobile Experts Limited.
* Copyright 2014 51Degrees Mobile Experts Limited, 5 Charlotte Close,
* Caversham, Reading, Berkshire, United Kingdom RG4 7BY and Yorkshire,
* Inc. Copyright 2014 Yorkshire, Inc, Guiyang, Guizhou, China
*
* This Source Code Form is the subject of the following patent
* applications, owned by 51Degrees Mobile Experts Limited of 5 Charlotte
* Close, Caversham, Reading, Berkshire, United Kingdom RG4 7BY:
* European Patent Application No. 13192291.6; and
* United States Patent Application Nos. 14/085,223 and 14/085,301.
*
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0.
*
* If a copy of the MPL was not distributed with this file, You can obtain
* one at http://mozilla.org/MPL/2.0/.
*
* This Source Code Form is "Incompatible With Secondary Licenses", as
* defined by the Mozilla Public License, v. 2.0.
********************************************************************** */
>>>>>>> V32

#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <v8.h>
#include "api.h"

using namespace v8;

TrieParser::TrieParser(char * filename, char * required_properties) {
<<<<<<< HEAD
  init_result = fiftyoneDegreesInitWithPropertyString(filename, required_properties);
=======
	init_result = fiftyoneDegreesInitWithPropertyString(filename, required_properties);
>>>>>>> V32
}

TrieParser::~TrieParser() {
}

void TrieParser::Init(Handle<Object> target) {
<<<<<<< HEAD
  NanScope();
  Local<FunctionTemplate> t = NanNew<FunctionTemplate>(New);
  // TODO(Yorkie): will remove
  t->InstanceTemplate()->SetInternalFieldCount(1);
  NODE_SET_PROTOTYPE_METHOD(t, "parse", Parse);
  target->Set(NanNew<String>("TrieParser"), t->GetFunction());
}

NAN_METHOD(TrieParser::New) {
  NanScope();
  char *filename;
  char *required_properties;

  // convert v8 objects to c/c++ types
  v8::String::Utf8Value v8_filename(args[0]->ToString());
  v8::String::Utf8Value v8_properties(args[1]->ToString());
  filename = *v8_filename;
  required_properties = *v8_properties;

  // create new instance of C++ class TrieParser
  TrieParser *parser = new TrieParser(filename, required_properties);
  parser->Wrap(args.This());

  // valid the database file content
  switch(parser->init_result) {
    case DATA_SET_INIT_STATUS_INSUFFICIENT_MEMORY:
      return NanThrowError("Insufficient memory");
    case DATA_SET_INIT_STATUS_CORRUPT_DATA:
      return NanThrowError("Device data file is corrupted");
    case DATA_SET_INIT_STATUS_INCORRECT_VERSION:
      return NanThrowError("Device data file is not correct");
    case DATA_SET_INIT_STATUS_FILE_NOT_FOUND:
      return NanThrowError("Device data file not found");
    default:
      NanReturnValue(args.This());
  }
}

NAN_METHOD(TrieParser::Parse) {
  NanScope();

  // convert v8 objects to c/c++ types
  char *input = NULL;
  Local<Object> result = NanNew<Object>();
  v8::String::Utf8Value v8_input(args[0]->ToString());
  input = *v8_input;
  
  int device = fiftyoneDegreesGetDeviceOffset(input);
  int index;
  int propCount = fiftyoneDegreesGetRequiredPropertiesCount();
  char **propNames = fiftyoneDegreesGetRequiredPropertiesNames();

  for (index = 0; index < propCount; index++) {
    char *key = *(propNames + index);
    int propIndex = fiftyoneDegreesGetPropertyIndex(key);
    char *val = fiftyoneDegreesGetValue(device, propIndex);
    if (strcmp(val, "True") == 0)
      result->Set(NanNew<v8::String>(key), NanTrue());
    else if (strcmp(val, "False") == 0)
      result->Set(NanNew<v8::String>(key), NanFalse());
    else
      result->Set(NanNew<v8::String>(key), NanNew<v8::String>(val));
  }

  NanReturnValue(result);
=======
	NanScope();
	Local<FunctionTemplate> t = NanNew<FunctionTemplate>(New);
	// TODO(Yorkie): will remove
	t->InstanceTemplate()->SetInternalFieldCount(1);
	NODE_SET_PROTOTYPE_METHOD(t, "parse", Parse);
	NODE_SET_PROTOTYPE_METHOD(t, "availableProperties", AvailableProperties);
	target->Set(NanNew<String>("TrieParser"), t->GetFunction());
}

NAN_METHOD(TrieParser::New) {
	NanScope();
	char *filename;
	char *required_properties;

	// convert v8 objects to c/c++ types
	v8::String::Utf8Value v8_filename(args[0]->ToString());
	v8::String::Utf8Value v8_properties(args[1]->ToString());
	filename = *v8_filename;
	required_properties = *v8_properties;

	// create new instance of C++ class TrieParser
	TrieParser *parser = new TrieParser(filename, required_properties);
	parser->Wrap(args.This());

	// valid the database file content
	switch (parser->init_result) {
	case DATA_SET_INIT_STATUS_NOT_SET:
		return NanThrowError("Device data file could not be initialised");
	case DATA_SET_INIT_STATUS_INSUFFICIENT_MEMORY:
		return NanThrowError("Insufficient memory");
	case DATA_SET_INIT_STATUS_CORRUPT_DATA:
		return NanThrowError("Device data file is corrupted");
	case DATA_SET_INIT_STATUS_INCORRECT_VERSION:
		return NanThrowError("Device data file is not correct");
	case DATA_SET_INIT_STATUS_FILE_NOT_FOUND:
		return NanThrowError("Device data file not found");
	default:
		NanReturnValue(args.This());
	}
}

NAN_METHOD(TrieParser::AvailableProperties) {
	NanScope();
	int requiredPropertyIndex;

	// convert v8 objects to c/c++ types
	TrieParser *parser = ObjectWrap::Unwrap<TrieParser>(args.This());

	// prepare the array with sufficient elements to store the required properties

	v8::Local<v8::Array> availableProperties = NanNew<v8::Array>(fiftyoneDegreesGetRequiredPropertiesCount());

	char **propNames = fiftyoneDegreesGetRequiredPropertiesNames();

	// add the available properties to the array
	for (requiredPropertyIndex = 0; requiredPropertyIndex < fiftyoneDegreesGetRequiredPropertiesCount(); requiredPropertyIndex++) {
		availableProperties->Set(requiredPropertyIndex, NanNew<String>(propNames[requiredPropertyIndex]));
	}

	// return the array of property names
	NanReturnValue(availableProperties);
}

NAN_METHOD(TrieParser::Parse) {
	NanScope();

	// convert v8 objects to c/c++ types
	char *input = NULL;
	Local<Object> result = NanNew<Object>();
	v8::String::Utf8Value v8_input(args[0]->ToString());
	input = *v8_input;

	int device = fiftyoneDegreesGetDeviceOffset(input);
	int index;
	int propCount = fiftyoneDegreesGetRequiredPropertiesCount();
	char **propNames = fiftyoneDegreesGetRequiredPropertiesNames();

	for (index = 0; index < propCount; index++) {
		char *key = *(propNames + index);
		int propIndex = fiftyoneDegreesGetPropertyIndex(key);
		char *val = fiftyoneDegreesGetValue(device, propIndex);
		if (strcmp(val, "True") == 0)
			result->Set(NanNew<v8::String>(key), NanTrue());
		else if (strcmp(val, "False") == 0)
			result->Set(NanNew<v8::String>(key), NanFalse());
		else
			result->Set(NanNew<v8::String>(key), NanNew<v8::String>(val));
	}

	NanReturnValue(result);
>>>>>>> V32
}

NODE_MODULE(trie, TrieParser::Init)

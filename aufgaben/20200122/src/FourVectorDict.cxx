// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME srcdIFourVectorDict
#define R__NO_DEPRECATION

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// The generated code does not explicitly qualifies STL entities
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "FourVector.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_FourVector(void *p = 0);
   static void *newArray_FourVector(Long_t size, void *p);
   static void delete_FourVector(void *p);
   static void deleteArray_FourVector(void *p);
   static void destruct_FourVector(void *p);
   static void streamer_FourVector(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FourVector*)
   {
      ::FourVector *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FourVector >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FourVector", ::FourVector::Class_Version(), "FourVector.h", 4,
                  typeid(::FourVector), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FourVector::Dictionary, isa_proxy, 16,
                  sizeof(::FourVector) );
      instance.SetNew(&new_FourVector);
      instance.SetNewArray(&newArray_FourVector);
      instance.SetDelete(&delete_FourVector);
      instance.SetDeleteArray(&deleteArray_FourVector);
      instance.SetDestructor(&destruct_FourVector);
      instance.SetStreamerFunc(&streamer_FourVector);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FourVector*)
   {
      return GenerateInitInstanceLocal((::FourVector*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::FourVector*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr FourVector::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FourVector::Class_Name()
{
   return "FourVector";
}

//______________________________________________________________________________
const char *FourVector::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FourVector*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FourVector::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FourVector*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FourVector::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FourVector*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FourVector::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FourVector*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void FourVector::Streamer(TBuffer &R__b)
{
   // Stream an object of class FourVector.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      R__b >> E;
      R__b >> Px;
      R__b >> Py;
      R__b >> Pz;
      R__b.CheckByteCount(R__s, R__c, FourVector::IsA());
   } else {
      R__c = R__b.WriteVersion(FourVector::IsA(), kTRUE);
      R__b << E;
      R__b << Px;
      R__b << Py;
      R__b << Pz;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FourVector(void *p) {
      return  p ? new(p) ::FourVector : new ::FourVector;
   }
   static void *newArray_FourVector(Long_t nElements, void *p) {
      return p ? new(p) ::FourVector[nElements] : new ::FourVector[nElements];
   }
   // Wrapper around operator delete
   static void delete_FourVector(void *p) {
      delete ((::FourVector*)p);
   }
   static void deleteArray_FourVector(void *p) {
      delete [] ((::FourVector*)p);
   }
   static void destruct_FourVector(void *p) {
      typedef ::FourVector current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FourVector(TBuffer &buf, void *obj) {
      ((::FourVector*)obj)->::FourVector::Streamer(buf);
   }
} // end of namespace ROOT for class ::FourVector

namespace {
  void TriggerDictionaryInitialization_FourVectorDict_Impl() {
    static const char* headers[] = {
"FourVector.h",
0
    };
    static const char* includePaths[] = {
"/usr/include",
"/home/robin/Documents/uni/Heidelberg/CPPdaten/aufgaben/20200122/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "FourVectorDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class __attribute__((annotate("$clingAutoload$FourVector.h")))  FourVector;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "FourVectorDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "FourVector.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"FourVector", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("FourVectorDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_FourVectorDict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_FourVectorDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_FourVectorDict() {
  TriggerDictionaryInitialization_FourVectorDict_Impl();
}

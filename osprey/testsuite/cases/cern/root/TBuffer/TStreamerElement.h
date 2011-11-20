

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TStreamerElement                                                     //
//                                                                      //
// Describe one element (data member) to be Streamed                    //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

//#ifndef ROOT_TNamed
#include "Rtypes.h"
//#endif

//class TMethodCall;
//class TClass;
//class TStreamerBasicType;

class TStreamerElement //: public TNamed 
{

protected:
   Int_t            fType;            //element type
   Int_t            fSize;            //sizeof element
   Int_t            fArrayLength;     //cumulative size of all array dims
   Int_t            fArrayDim;        //number of array dimensions
   Int_t            fMaxIndex[5];     //Maximum array index for array dimension "dim"
   Int_t            fOffset;          //!element offset in class
   Int_t            fTObjectOffset;   //!base offset for TObject if the element inherits from it
   Int_t            fNewType;         //!new element type when reading
   //TString          fTypeName;        //Data type name of data member
   //TClass          *fClassObject;     //!pointer to class of object
   //TMemberStreamer *fStreamer;        //!pointer to element Streamer
   //TMethodCall     *fMethod;          //!pointer to TMethodCall
   Double_t         fXmin;            //!Minimum of data member if a range is specified  [xmin,xmax,nbits]
   Double_t         fXmax;            //!Maximum of data member if a range is specified  [xmin,xmax,nbits]
   Double_t         fFactor;          //!Conversion factor if a range is specified fFactor = (1<<nbits/(xmax-xmin)

public:

   enum ESTLtype { kSTL       = 300 /* TStreamerInfo::kSTL */, 
                   kSTLstring = 365 /* TStreamerInfo::kSTLstring */,   
                   kSTLvector = 1,
                   kSTLlist   =  2,  kSTLdeque   =  3,   kSTLmap    = 4,
                   kSTLset    =  5,  kSTLmultimap=6,     kSTLmultiset=7};
   // TStreamerElement status bits
   enum {
      kHasRange     = BIT(6)
   };

   TStreamerElement();
  
 /* TStreamerElement(const char *name, const char *title, Int_t offset, Int_t dtype, const char *typeName);
   virtual         ~TStreamerElement();
   virtual Bool_t   CannotSplit() const;
   Int_t            GetArrayDim() const {return fArrayDim;}
   Int_t            GetArrayLength() const {return fArrayLength;}
   virtual TClass  *GetClassPointer() const;
           TClass  *GetClass()        const {return GetClassPointer();} 
   virtual Int_t    GetExecID() const;
   virtual const char *GetFullName() const;
   virtual const char *GetInclude() const {return "";}
   Int_t            GetMaxIndex(Int_t i) const {return fMaxIndex[i];}
   virtual ULong_t  GetMethod() const {return ULong_t(fStreamer);}
   TMemberStreamer *GetStreamer() const;
   virtual Int_t    GetSize() const;
   Int_t            GetNewType() const {return fNewType;}
   Int_t            GetType() const {return fType;}
   Int_t            GetOffset() const {return fOffset;}
   Int_t            GetTObjectOffset() const { return fTObjectOffset; }
   const char      *GetTypeName() const {return fTypeName.Data();}
   const char      *GetTypeNameBasic() const;
  */ Double_t         GetFactor() const {return fFactor;}
   Double_t         GetXmin()   const {return fXmin;}
   Double_t         GetXmax()   const {return fXmax;}
};

/*   virtual void     Init(TObject *obj=0);
   virtual Bool_t   IsaPointer() const {return kFALSE;}
   virtual Bool_t   HasCounter() const {return kFALSE;}
   virtual Bool_t   IsOldFormat(const char *newTypeName);
   virtual Bool_t   IsBase() const;
   virtual void     ls(Option_t *option="") const;
   virtual void     SetArrayDim(Int_t dim);
   virtual void     SetMaxIndex(Int_t dim, Int_t max);
   virtual void     SetOffset(Int_t offset) {fOffset=offset;}
   virtual void     SetTObjectOffset(Int_t tobjoffset) {fTObjectOffset=tobjoffset;}
   virtual void     SetStreamer(TMemberStreamer *streamer);
   virtual void     SetSize(Int_t dsize) {fSize = dsize;}
   virtual void     SetNewType(Int_t dtype) {fNewType = dtype;}
   virtual void     SetType(Int_t dtype) {fType = dtype;}
   virtual void     SetTypeName(const char *name) {fTypeName = name;}
   virtual void     Update(const TClass *oldClass, TClass *newClass);

   ClassDef(TStreamerElement,4)  //Base class for one element (data member) to be Streamed
};

//________________________________________________________________________
class TStreamerBase : public TStreamerElement {

protected:
   Int_t            fBaseVersion;         //version number of the base class
   TClass          *fBaseClass;           //!pointer to base class

public:

   TStreamerBase();
   TStreamerBase(const char *name, const char *title, Int_t offset);
   virtual         ~TStreamerBase();
   Int_t            GetBaseVersion() {return fBaseVersion;}
   virtual TClass  *GetClassPointer() const;
   const char      *GetInclude() const;
   ULong_t          GetMethod() const {return ULong_t(fMethod);}
   Int_t            GetSize() const;
   virtual void     Init(TObject *obj=0);
   Bool_t           IsBase() const;
   virtual void     ls(Option_t *option="") const;
   Int_t            ReadBuffer (TBuffer &b, char *pointer);
   void             SetBaseVersion(Int_t v) {fBaseVersion = v;}
   virtual void     Update(const TClass *oldClass, TClass *newClass);
   Int_t            WriteBuffer(TBuffer &b, char *pointer);

   ClassDef(TStreamerBase,3)  //Streamer element of type base class
};

//________________________________________________________________________
class TStreamerBasicPointer : public TStreamerElement {

protected:
   Int_t               fCountVersion;   //version number of the class with the counter
   TString             fCountName;      //name of data member holding the array count
   TString             fCountClass;     //name of the class with the counter
   TStreamerBasicType *fCounter;        //!pointer to basic type counter

public:

   TStreamerBasicPointer();
   TStreamerBasicPointer(const char *name, const char *title, Int_t offset, Int_t dtype, 
                         const char *countName, const char *countClass, Int_t version, const char *typeName);
   virtual       ~TStreamerBasicPointer();
   const char    *GetCountClass()   const {return fCountClass.Data();}
   const char    *GetCountName()    const {return fCountName.Data();}
   Int_t          GetCountVersion() const {return fCountVersion;}
   ULong_t        GetMethod() const;
   Int_t          GetSize() const;
   virtual void   Init(TObject *obj=0);
   virtual Bool_t HasCounter() const                {return fCounter!=0;   }
   virtual Bool_t IsaPointer() const                {return kTRUE;         }
   void           SetArrayDim(Int_t dim);
   void           SetCountClass(const char *clname) {fCountClass = clname; }
   void           SetCountName(const char *name)    {fCountName = name;    }
   void           SetCountVersion(Int_t count)      {fCountVersion = count;}
   
   ClassDef(TStreamerBasicPointer,2)  //Streamer element for a pointer to a basic type
};

//________________________________________________________________________
class TStreamerLoop : public TStreamerElement {

protected:
   Int_t               fCountVersion;   //version number of the class with the counter
   TString             fCountName;      //name of data member holding the array count
   TString             fCountClass;     //name of the class with the counter
   TStreamerBasicType *fCounter;        //!pointer to basic type counter

public:

   TStreamerLoop();
   TStreamerLoop(const char *name, const char *title, Int_t offset, const char *countName, const char *countClass, Int_t version, const char *typeName);
   virtual       ~TStreamerLoop();
   const char    *GetCountClass()   const {return fCountClass.Data();}
   const char    *GetCountName()    const {return fCountName.Data();}
   Int_t          GetCountVersion() const {return fCountVersion;}
   const char    *GetInclude() const;
   ULong_t        GetMethod() const;
   Int_t          GetSize() const;
   virtual void   Init(TObject *obj=0);
   virtual Bool_t IsaPointer() const                {return kTRUE;         }
   virtual Bool_t HasCounter() const                {return fCounter!=0;   }
   void           SetCountClass(const char *clname) {fCountClass = clname; }
   void           SetCountName(const char *name)    {fCountName = name;    }
   void           SetCountVersion(Int_t count)      {fCountVersion = count;}

   ClassDef(TStreamerLoop,2)  //Streamer element for a pointer to an array of objects
};

//________________________________________________________________________
class TStreamerBasicType : public TStreamerElement {

protected:
   Int_t             fCounter;     //!value of data member when referenced by an array

public:

   TStreamerBasicType();
   TStreamerBasicType(const char *name, const char *title, Int_t offset, Int_t dtype, const char *typeName);
   virtual       ~TStreamerBasicType();
   Int_t          GetCounter() const {return fCounter;}
   ULong_t        GetMethod() const;
   Int_t          GetSize() const;

   ClassDef(TStreamerBasicType,2)  //Streamer element for a basic type
};

//________________________________________________________________________
class TStreamerObject : public TStreamerElement {

public:

   TStreamerObject();
   TStreamerObject(const char *name, const char *title, Int_t offset, const char *typeName);
   virtual       ~TStreamerObject();
   const char    *GetInclude() const;
   Int_t          GetSize() const;
   virtual void   Init(TObject *obj=0);

   ClassDef(TStreamerObject,2)  //Streamer element of type object
};

//________________________________________________________________________
class TStreamerObjectAny : public TStreamerElement {

public:

   TStreamerObjectAny();
   TStreamerObjectAny(const char *name, const char *title, Int_t offset, const char *typeName);
   virtual       ~TStreamerObjectAny();
   const char    *GetInclude() const;
   Int_t          GetSize() const;
   virtual void   Init(TObject *obj=0);

   ClassDef(TStreamerObjectAny,2)  //Streamer element of type object other than TObject
};

//________________________________________________________________________
class TStreamerObjectPointer : public TStreamerElement {

public:

   TStreamerObjectPointer();
   TStreamerObjectPointer(const char *name, const char *title, Int_t offset, const char *typeName);
   virtual       ~TStreamerObjectPointer();
   const char    *GetInclude() const;
   Int_t          GetSize() const;
   virtual void   Init(TObject *obj=0);
   virtual Bool_t IsaPointer() const {return kTRUE;}
   virtual void   SetArrayDim(Int_t dim);

   ClassDef(TStreamerObjectPointer,2)  //Streamer element of type pointer to a TObject
};

//________________________________________________________________________
class TStreamerObjectAnyPointer : public TStreamerElement {

public:

   TStreamerObjectAnyPointer();
   TStreamerObjectAnyPointer(const char *name, const char *title, Int_t offset, const char *typeName);
   virtual       ~TStreamerObjectAnyPointer();
   const char    *GetInclude() const;
   Int_t          GetSize() const;
   virtual void   Init(TObject *obj=0);
   virtual Bool_t IsaPointer() const {return kTRUE;}
   virtual void   SetArrayDim(Int_t dim);
   
   ClassDef(TStreamerObjectAnyPointer,1)  //Streamer element of type pointer to a non TObject
};

//________________________________________________________________________
class TStreamerString : public TStreamerElement {

public:

   TStreamerString();
   TStreamerString(const char *name, const char *title, Int_t offset);
   virtual       ~TStreamerString();
   Int_t          GetSize() const;

   ClassDef(TStreamerString,2)  //Streamer element of type TString
};

//________________________________________________________________________
class TStreamerSTL : public TStreamerElement {

protected:
   Int_t       fSTLtype;       //type of STL vector
   Int_t       fCtype;         //STL contained type

public:

   TStreamerSTL();
   TStreamerSTL(const char *name, const char *title, Int_t offset, 
                const char *typeName, const char *trueType, Bool_t dmPointer);
   virtual       ~TStreamerSTL();
   Bool_t         CannotSplit() const;
   Bool_t         IsaPointer() const;
   Bool_t         IsBase() const;
   Int_t          GetSTLtype() const {return fSTLtype;}
   Int_t          GetCtype()   const {return fCtype;}
   const char    *GetInclude() const;
   Int_t          GetSize() const;
   virtual void   ls(Option_t *option="") const;
   void           SetSTLtype(Int_t t) {fSTLtype = t;}
   void           SetCtype(Int_t t) {fCtype = t;}
   virtual void   SetStreamer(TMemberStreamer *streamer);

   ClassDef(TStreamerSTL,3)  //Streamer element of type STL container
};

//________________________________________________________________________
class TStreamerSTLstring : public TStreamerSTL {

public:

   TStreamerSTLstring();
   TStreamerSTLstring(const char *name, const char *title, Int_t offset,
                      const char *typeName, Bool_t dmPointer);
   virtual       ~TStreamerSTLstring();
   const char    *GetInclude() const;
   Int_t          GetSize() const;

   ClassDef(TStreamerSTLstring,2)  //Streamer element of type  C++ string
};

#endif*/

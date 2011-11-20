class TGeoBBox : public TGeoShape
{
	protected :
//~ // data members
   Double_t              fDX;        // X half-length
   Double_t              fDY;        // Y half-length
   Double_t              fDZ;        // Z half-length
   Double_t              fOrigin[3]; // box origin
//~ // methods
   //~ virtual void FillBuffer3D(TBuffer3D & buffer, Int_t reqSections, Bool_t localFrame) const;
	public:
   //~ // constructors
   //~ TGeoBBox();
   TGeoBBox(Double_t dx, Double_t dy, Double_t dz, Double_t *origin=0);
   //~ TGeoBBox(const char *name, Double_t dx, Double_t dy, Double_t dz, Double_t *origin=0);
   //~ TGeoBBox(Double_t *param);
   //~ // destructor
   //~ virtual ~TGeoBBox();
   //~ // methods
   //~ virtual void          ComputeBBox();
   //~ virtual void          ComputeNormal(Double_t *point, Double_t *dir, Double_t *norm);
   //~ virtual Bool_t        Contains(Double_t *point) const;
   //~ virtual Bool_t        CouldBeCrossed(Double_t *point, Double_t *dir) const;
   //~ virtual Int_t         DistancetoPrimitive(Int_t px, Int_t py);
   //~ virtual Double_t      DistFromInside(Double_t *point, Double_t *dir, Int_t iact=1, 
                                   //~ Double_t step=TGeoShape::Big(), Double_t *safe=0) const;
   //~ virtual Double_t      DistFromOutside(Double_t *point, Double_t *dir, Int_t iact=1, 
                                   //~ Double_t step=TGeoShape::Big(), Double_t *safe=0) const;
   //~ virtual TGeoVolume   *Divide(TGeoVolume *voldiv, const char *divname, Int_t iaxis, Int_t ndiv, 
                                //~ Double_t start, Double_t step);
   //~ virtual const char   *GetAxisName(Int_t iaxis) const;
   //~ virtual Double_t      GetAxisRange(Int_t iaxis, Double_t &xlo, Double_t &xhi) const;
   //~ virtual void          GetBoundingCylinder(Double_t *param) const;
   //~ virtual const TBuffer3D &GetBuffer3D(Int_t reqSections, Bool_t localFrame) const;
   //~ virtual Int_t         GetByteCount() const {return 36;}
   //~ virtual Int_t         GetFittingBox(const TGeoBBox *parambox, TGeoMatrix *mat, Double_t &dx, Double_t &dy, Double_t &dz) const;
   //~ virtual TGeoShape    *GetMakeRuntimeShape(TGeoShape *mother, TGeoMatrix *mat) const;
   //~ virtual Int_t         GetNmeshVertices() const {return 8;}
   //~ virtual Double_t      GetDX() const  {return fDX;}
   //~ virtual Double_t      GetDY() const  {return fDY;}
   //~ virtual Double_t      GetDZ() const  {return fDZ;}
   //~ virtual const Double_t *GetOrigin() const {return fOrigin;}
   //~ virtual void          InspectShape() const;
   //~ virtual Bool_t        IsCylType() const {return kFALSE;}
   //~ virtual Bool_t        IsValidBox() const {return ((fDX<0)||(fDY<0)||(fDZ<0))?kFALSE:kTRUE;}
   //~ virtual Bool_t        IsNullBox() const {return ((fDX==0)&&(fDY==0)&&(fDZ==0))?kTRUE:kFALSE;}
   //~ virtual TBuffer3D    *MakeBuffer3D() const;
   //~ virtual Double_t      Safety(Double_t *point, Bool_t in=kTRUE) const;
   //~ virtual void          SavePrimitive(ofstream &out, Option_t *option);
   void                  SetBoxDimensions(Double_t dx, Double_t dy, Double_t dz, Double_t *origin=0);
   //~ virtual void          SetDimensions(Double_t *param);
   //~ void                  SetBoxPoints(Double_t *points) const;
   //~ virtual void          SetPoints(Double_t *points) const;
   //~ virtual void          SetPoints(Float_t *points) const;
   //~ virtual void          SetSegsAndPols(TBuffer3D &buffer) const;
   //~ virtual void          Sizeof3D() const;

  //~ ClassDef(TGeoBBox, 1)         // box primitive
};


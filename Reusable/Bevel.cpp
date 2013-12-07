#include "Bevel.h"

DBevel::DBevel(BRect frame,const char* name,BevelKind Kind,uint32 resizingMode = B_FOLLOW_LEFT | B_FOLLOW_TOP,uint32 flags = B_WILL_DRAW) :
        BView(frame,name,resizingMode,flags)
{
  fKind = Kind;
  SetDrawingMode(B_OP_OVER);
};

void
DBevel::SetKind(BevelKind Kind)
{
  fKind = Kind;
  Draw(Bounds());
};

BevelKind
DBevel::Kind(void)
{
  return fKind;
};

void
DBevel::SetText(char* Text)
{
  fText = Text;
};

char*
DBevel::Text(void)
{
  return fText;
};

void
DBevel::SetAlignment(alignment TextAlignment)
{
  fTextAlignment = TextAlignment;
};

alignment
DBevel::Alignment(void)
{
  return fTextAlignment;
};

void
DBevel::Draw(BRect updateRect)
{
  BRect bounds = Bounds();
  SetHighColor(ViewColor());
  switch(fKind) {
    case kLoweredBox: {
      FillRect(bounds);
      BeginLineArray(8);
      AddLine(BPoint(bounds.left,bounds.top),BPoint(bounds.right-1,bounds.top),clDarkGray);
      AddLine(BPoint(bounds.left+1,bounds.top+1),BPoint(bounds.right,bounds.top+1),clWhite);
      AddLine(BPoint(bounds.left,bounds.top),BPoint(bounds.left,bounds.bottom-1),clDarkGray);
      AddLine(BPoint(bounds.left+1,bounds.top+1),BPoint(bounds.left+1,bounds.bottom),clWhite);
      AddLine(BPoint(bounds.right,bounds.top+1),BPoint(bounds.right,bounds.bottom),clWhite);
      AddLine(BPoint(bounds.right-1,bounds.top),BPoint(bounds.right-1,bounds.bottom),clDarkGray);
      AddLine(BPoint(bounds.left+1,bounds.bottom),BPoint(bounds.right,bounds.bottom),clWhite);
      AddLine(BPoint(bounds.left,bounds.bottom-1),BPoint(bounds.right-1,bounds.bottom-1),clDarkGray);
      EndLineArray();
      break;
    };
    case kRaisedBox: {
      FillRect(bounds);
      BeginLineArray(8);
      AddLine(BPoint(bounds.left,bounds.top),BPoint(bounds.right,bounds.top),clWhite);
      AddLine(BPoint(bounds.left+1,bounds.top+1),BPoint(bounds.right,bounds.top+1),clDarkGray);
      AddLine(BPoint(bounds.left,bounds.top),BPoint(bounds.left,bounds.bottom),clWhite);
      AddLine(BPoint(bounds.left+1,bounds.top+1),BPoint(bounds.left+1,bounds.bottom),clDarkGray);
      AddLine(BPoint(bounds.right,bounds.top),BPoint(bounds.right,bounds.bottom),clDarkGray);
      AddLine(BPoint(bounds.right-1,bounds.top),BPoint(bounds.right-1,bounds.bottom),clWhite);
      AddLine(BPoint(bounds.left,bounds.bottom),BPoint(bounds.right,bounds.bottom),clDarkGray);
      AddLine(BPoint(bounds.left,bounds.bottom-1),BPoint(bounds.right-1,bounds.bottom-1),clWhite);
      EndLineArray();
      break;
    };
    case kTopLine: {
      FillRect(bounds);
      BeginLineArray(2);
      AddLine(BPoint(bounds.left,bounds.top),BPoint(bounds.right,bounds.top),clDarkGray);
      AddLine(BPoint(bounds.left,bounds.top+1),BPoint(bounds.right,bounds.top+1),clWhite);
      EndLineArray();
      break;
    };
    case kBottomLine: {
      FillRect(bounds);
      BeginLineArray(2);
      AddLine(BPoint(bounds.left,bounds.bottom),BPoint(bounds.right,bounds.bottom),clDarkGray);
      AddLine(BPoint(bounds.left,bounds.bottom-1),BPoint(bounds.right-1,bounds.bottom-1),clWhite);
      EndLineArray();
      break;
    };
    case kLeftLine: {
      FillRect(bounds);
      BeginLineArray(2);
      AddLine(BPoint(bounds.left,bounds.top),BPoint(bounds.left,bounds.bottom),clDarkGray);
      AddLine(BPoint(bounds.left+1,bounds.top+1),BPoint(bounds.left+1,bounds.bottom),clWhite);
      EndLineArray();
      break;
    };
    case kRightLine: {
      FillRect(bounds);
      BeginLineArray(2);
      AddLine(BPoint(bounds.right,bounds.top),BPoint(bounds.right,bounds.bottom),clDarkGray);
      AddLine(BPoint(bounds.right-1,bounds.top),BPoint(bounds.right-1,bounds.bottom),clWhite);
      EndLineArray();
      break;
    };
    default: BView::Draw(updateRect); break;
  };
};
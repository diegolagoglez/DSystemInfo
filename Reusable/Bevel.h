//************************************************************//
//                                                            //
//     DBevel class - Nov 2000                                //
//     version 1.0                                            //
//     Developed by chairman                                  //
//     Spain                                                  //
//                                                            //
//************************************************************//

#ifndef _BEVEL_H_
#define _BEVEL_H_

#include <InterfaceDefs.h>
#include <View.h>

const rgb_color clWhite       = { 255,255,255,255 };
const rgb_color clBlack       = { 0,0,0,255 };
const rgb_color clDarkGray    = { 170,170,170,255 };
const rgb_color clBeOSGray    = { 222,222,222,255 };

enum BevelKind {
      kLoweredBox,
      kRaisedBox,
      kTopLine,
      kBottomLine,
      kLeftLine,
      kRightLine
    };

class DBevel : public BView
{
  public:
    DBevel(BRect frame,
           const char* name,
           BevelKind Kind,
           uint32 resizingMode = B_FOLLOW_LEFT | B_FOLLOW_TOP,
           uint32 flags = B_WILL_DRAW);
    virtual void Draw(BRect);   // do not draw the text at this time
    void SetKind(BevelKind);
    BevelKind Kind(void);
    void SetText(char*);
    char* Text(void);
    void SetAlignment(alignment);
    alignment Alignment(void);
  private:
    BevelKind fKind;
    char* fText;
    alignment fTextAlignment;
};

#endif
/*
  xdrv_13_display.ino - Display support for Sonoff-Tasmota

  Copyright (C) 2018  Theo Arends, Gerhard Mutz

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#if defined(USE_I2C) || defined(USE_SPI)
#ifdef USE_DISPLAY
#include <renderer.h>
#include <FT6236.h>

Renderer *renderer;

enum ColorType { COLOR_BW,COLOR_COLOR};

// drawing color is WHITE
// on epaper the whole display buffer is transfered inverted this results in white paper
uint16_t fg_color = 1;
uint16_t bg_color = 0;
uint8_t color_type = COLOR_BW;
uint8_t auto_draw=1;

extern TouchLocation pLoc;

#define MAXBUTTONS 16

#ifdef USE_TOUCH_BUTTONS
Adafruit_GFX_Button *buttons[MAXBUTTONS];
#endif

#define DISPLAY_MAX_DRIVERS    16           // Max number of display drivers/models supported by xdsp_interface.ino
#define DISPLAY_MAX_COLS       40           // Max number of columns to display
#define DISPLAY_MAX_ROWS       16           // Max number of lines to display for LCD and Oled using local screen buffer

#define DISPLAY_LOG_COLS       DISPLAY_MAX_COLS +1  // Number of characters in display log buffer line +1
#define DISPLAY_LOG_ROWS       32           // Number of lines in display log buffer

#define D_CMND_DISPLAY "Display"
#define D_CMND_DISP_ADDRESS "Address"
#define D_CMND_DISP_COLS "Cols"
#define D_CMND_DISP_DIMMER "Dimmer"
#define D_CMND_DISP_MODE "Mode"
#define D_CMND_DISP_MODEL "Model"
#define D_CMND_DISP_REFRESH "Refresh"
#define D_CMND_DISP_ROWS "Rows"
#define D_CMND_DISP_SIZE "Size"
#define D_CMND_DISP_FONT "Font"
#define D_CMND_DISP_ROTATE "Rotate"
#define D_CMND_DISP_TEXT "Text"

enum XdspFunctions { FUNC_DISPLAY_INIT_DRIVER, FUNC_DISPLAY_INIT, FUNC_DISPLAY_EVERY_50_MSECOND, FUNC_DISPLAY_EVERY_SECOND,
                     FUNC_DISPLAY_MODEL, FUNC_DISPLAY_MODE, FUNC_DISPLAY_POWER,
                     FUNC_DISPLAY_CLEAR, FUNC_DISPLAY_DRAW_FRAME,
                     FUNC_DISPLAY_DRAW_HLINE, FUNC_DISPLAY_DRAW_VLINE, FUNC_DISPLAY_DRAW_LINE,
                     FUNC_DISPLAY_DRAW_CIRCLE, FUNC_DISPLAY_FILL_CIRCLE,
                     FUNC_DISPLAY_DRAW_RECTANGLE, FUNC_DISPLAY_FILL_RECTANGLE,
                     FUNC_DISPLAY_TEXT_SIZE, FUNC_DISPLAY_FONT_SIZE, FUNC_DISPLAY_ROTATION, FUNC_DISPLAY_DRAW_STRING, FUNC_DISPLAY_ONOFF };


enum DisplayInitModes { DISPLAY_INIT_MODE, DISPLAY_INIT_PARTIAL, DISPLAY_INIT_FULL };

enum DisplayCommands { CMND_DISPLAY, CMND_DISP_MODEL, CMND_DISP_MODE, CMND_DISP_REFRESH, CMND_DISP_DIMMER, CMND_DISP_COLS, CMND_DISP_ROWS,
  CMND_DISP_SIZE,CMND_DISP_FONT,CMND_DISP_ROTATE, CMND_DISP_TEXT, CMND_DISP_ADDRESS };
const char kDisplayCommands[] PROGMEM =  "|"
  D_CMND_DISP_MODEL "|" D_CMND_DISP_MODE "|" D_CMND_DISP_REFRESH "|" D_CMND_DISP_DIMMER "|" D_CMND_DISP_COLS "|" D_CMND_DISP_ROWS "|"
  D_CMND_DISP_SIZE "|" D_CMND_DISP_FONT "|" D_CMND_DISP_ROTATE "|" D_CMND_DISP_TEXT "|" D_CMND_DISP_ADDRESS ;

const char S_JSON_DISPLAY_COMMAND_VALUE[] PROGMEM =        "{\"" D_CMND_DISPLAY "%s\":\"%s\"}";
const char S_JSON_DISPLAY_COMMAND_NVALUE[] PROGMEM =       "{\"" D_CMND_DISPLAY "%s\":%d}";
const char S_JSON_DISPLAY_COMMAND_INDEX_NVALUE[] PROGMEM = "{\"" D_CMND_DISPLAY "%s%d\":%d}";

uint8_t disp_power = 0;
uint8_t disp_device = 0;
uint8_t disp_refresh = 1;

int16_t disp_xpos = 0;
int16_t disp_ypos = 0;
uint8_t dsp_init;
uint8_t dsp_on;
uint16_t dsp_x;
uint16_t dsp_y;
uint16_t dsp_x2;
uint16_t dsp_y2;
uint16_t dsp_rad;
uint16_t dsp_color;
int16_t dsp_len;
char *dsp_str;
uint8_t dsp_flag;

#ifdef USE_DISPLAY_MODES1TO5
char disp_log_buffer[DISPLAY_LOG_ROWS][DISPLAY_LOG_COLS];
char disp_temp[2];    // C or F
uint8_t disp_log_buffer_idx = 0;
uint8_t disp_log_buffer_ptr = 0;
bool disp_log_buffer_active = false;
uint8_t disp_subscribed = 0;
#endif  // USE_DISPLAY_MODES1TO5

/*********************************************************************************************/


#define USE_GRAPH
#define USE_AWATCH

#define NUM_GRAPHS 4

#ifdef USE_AWATCH
#define MINUTE_REDUCT 4

// draw analog watch, just for fun
void DrawAClock(uint16_t rad) {
    float frad=rad;
    uint16_t hred=frad/3.0;
    renderer->fillCircle(disp_xpos, disp_ypos, rad, bg_color);
    renderer->drawCircle(disp_xpos, disp_ypos, rad, fg_color);
    renderer->fillCircle(disp_xpos, disp_ypos, 4, fg_color);
    for (uint8_t count=0; count<60; count+=5) {
      float p1=((float)count*(pi/30)-(pi/2));
      uint8_t len;
      if ((count%15)==0) {
        len=4;
      } else {
        len=2;
      }
      renderer->writeLine(disp_xpos+((float)(rad-len)*cos(p1)), disp_ypos+((float)(rad-len)*sin(p1)), disp_xpos+(frad*cos(p1)), disp_ypos+(frad*sin(p1)), fg_color);
    }

    // hour
    float hour=((float)RtcTime.hour*60.0+(float)RtcTime.minute)/60.0;
    float temp=(hour*(pi/6.0)-(pi/2.0));
    renderer->writeLine(disp_xpos, disp_ypos,disp_xpos+(frad-hred)*cos(temp),disp_ypos+(frad-hred)*sin(temp), fg_color);

    // minute
    temp=((float)RtcTime.minute*(pi/30.0)-(pi/2.0));
    renderer->writeLine(disp_xpos, disp_ypos,disp_xpos+(frad-MINUTE_REDUCT)*cos(temp),disp_ypos+(frad-MINUTE_REDUCT)*sin(temp), fg_color);
}
#endif


#ifdef USE_GRAPH

struct GRAPH {
  uint16_t xp;
  uint16_t yp;
  uint16_t xs;
  uint16_t ys;
  float ymin;
  float ymax;
  float range;
  uint32_t x_time;       // time per x slice in milliseconds
  uint32_t last_ms;
  uint32_t last_ms_redrawn;
  int16_t decimation; // decimation or graph duration in minutes
  uint16_t dcnt;
  uint32_t summ;
  uint16_t xcnt;
  uint8_t *values;
  uint8_t xticks;
  uint8_t yticks;
  uint8_t last_val;
  uint8_t color_index;
  uint8_t flags;
};


struct GRAPH *graph[NUM_GRAPHS];

#define TICKLEN 4
void ClrGraph(uint16_t num) {
  struct GRAPH *gp=graph[num];

  uint16_t xticks=gp->xticks;
  uint16_t yticks=gp->yticks;
  uint16_t count;

  // clr inside, but only 1.graph if overlapped
  if (gp->flags) return;

  renderer->fillRect(gp->xp+1,gp->yp+1,gp->xs-2,gp->ys-2,bg_color);

  if (xticks) {
    float cxp=gp->xp,xd=(float)gp->xs/(float)xticks;
    for (count=0; count<xticks; count++) {
      renderer->writeFastVLine(cxp,gp->yp+gp->ys-TICKLEN,TICKLEN,fg_color);
      cxp+=xd;
    }
  }
  if (yticks) {
    if (gp->ymin<0 && gp->ymax>0) {
      // draw zero seperator
      float cxp=0;
      float czp=gp->yp+(gp->ymax/gp->range);
      while (cxp<gp->xs) {
        renderer->writeFastHLine(gp->xp+cxp,czp,2,fg_color);
        cxp+=6.0;
      }
      // align ticks to zero line
      float cyp=0,yd=gp->ys/yticks;
      for (count=0; count<yticks; count++) {
        if ((czp-cyp)>gp->yp) {
          renderer->writeFastHLine(gp->xp,czp-cyp,TICKLEN,fg_color);
          renderer->writeFastHLine(gp->xp+gp->xs-TICKLEN,czp-cyp,TICKLEN,fg_color);
        }
        if ((czp+cyp)<(gp->yp+gp->ys)) {
          renderer->writeFastHLine(gp->xp,czp+cyp,TICKLEN,fg_color);
          renderer->writeFastHLine(gp->xp+gp->xs-TICKLEN,czp+cyp,TICKLEN,fg_color);
        }
        cyp+=yd;
      }
    } else {
      float cyp=gp->yp,yd=gp->ys/yticks;
      for (count=0; count<yticks; count++) {
        renderer->writeFastHLine(gp->xp,cyp,TICKLEN,fg_color);
        renderer->writeFastHLine(gp->xp+gp->xs-TICKLEN,cyp,TICKLEN,fg_color);
        cyp+=yd;
      }
    }
  }
}

// define a graph
void DefineGraph(uint16_t num,uint16_t xp,uint16_t yp,uint16_t xs,uint16_t ys,int16_t dec,float ymin, float ymax,uint8_t icol) {
  if (!renderer) return;

  struct GRAPH *gp;
  uint16_t count;
  uint16_t index=num%NUM_GRAPHS;
  if (!graph[index]) {
    gp=(struct GRAPH*)calloc(sizeof(struct GRAPH),1);
    if (!gp) return;
    graph[index]=gp;
  } else {
    gp=graph[index];
  }

  gp->xticks=(num>>2)&0x3f;
  gp->yticks=(num>>8)&0x3f;
  gp->xp=xp;
  gp->yp=yp;
  gp->xs=xs;
  gp->ys=ys;
  if (!dec) dec=1;
  gp->decimation=dec;
  if (dec>0) {
    // is minutes per sweep prepare timing parameters in ms
    gp->x_time=(dec*60000)/(float)xs;
    gp->last_ms=millis()+gp->x_time;
  }
  gp->ymin=ymin;
  gp->ymax=ymax;
  gp->range=(ymax-ymin)/ys;
  gp->xcnt=0;
  gp->dcnt=0;
  gp->summ=0;
  if (gp->values) free(gp->values);
  gp->values=(uint8_t*) calloc(1,xs+2);
  if (!gp->values) {
    free(gp);
    graph[index]=0;
    return;
  }
  // start from zero
  gp->values[0]=0;

  gp->last_ms_redrawn=millis();

  if (!icol) icol=1;
  gp->color_index=icol;
  gp->flags=0;

  // check if previous graph has same coordinates
  if (index>0) {
    for (uint8_t count=0; count<index; count++) {
      if (graph[count]) {
        // a previous graph is defined, compare
        // assume the same if corner is identical
        struct GRAPH *gp1=graph[count];
        if ((gp->xp==gp1->xp) && (gp->yp==gp1->yp)) {
          gp->flags=1;
          break;
        }
      }
    }
  }

  // draw rectangle
  renderer->drawRect(xp,yp,xs,ys,fg_color);
  // clr inside
  ClrGraph(index);

}

// check if to advance GRAPH
void DisplayCheckGraph() {
  int16_t count;
  struct GRAPH *gp;
  for (count=0;count<NUM_GRAPHS;count++) {
    gp=graph[count];
    if (gp) {
      if (gp->decimation>0) {
        // if time over add value
        while (millis()>gp->last_ms) {
          gp->last_ms+=gp->x_time;
          uint8_t val;
          if (gp->dcnt) {
            val=gp->summ/gp->dcnt;
            gp->dcnt=0;
            gp->summ=0;
            gp->last_val=val;
          } else {
            val=gp->last_val;
          }
          AddGraph(count,val);
        }
      }
    }
  }
}

// add next value to graph
void AddGraph(uint8_t num,uint8_t val) {
  struct GRAPH *gp=graph[num];
  if (!renderer) return;

  uint16_t linecol=fg_color;
  if (color_type==COLOR_COLOR) {
    linecol=renderer->GetColorFromIndex(gp->color_index);
  }
  gp->xcnt++;
  if (gp->xcnt>gp->xs) {
    gp->xcnt=gp->xs;
    int16_t count;
    // shift values
    for (count=0;count<gp->xs-1;count++) {
      gp->values[count]=gp->values[count+1];
    }
    gp->values[gp->xcnt-1]=val;

    // only redraw every second or longer
    if (millis()-gp->last_ms_redrawn>1000) {
      gp->last_ms_redrawn=millis();
      // clr area and redraw graph
      if (!gp->flags) {
        // draw rectangle
        renderer->drawRect(gp->xp,gp->yp,gp->xs,gp->ys,fg_color);
        // clr inner and draw ticks
        ClrGraph(num);
      }

      for (count=0;count<gp->xs-1;count++) {
        renderer->writeLine(gp->xp+count,gp->yp+gp->ys-gp->values[count]-1,gp->xp+count+1,gp->yp+gp->ys-gp->values[count+1]-1,linecol);
      }
    }
  } else {
    // add value and draw a single line
    gp->values[gp->xcnt]=val;
    renderer->writeLine(gp->xp+gp->xcnt-1,gp->yp+gp->ys-gp->values[gp->xcnt-1]-1,gp->xp+gp->xcnt,gp->yp+gp->ys-gp->values[gp->xcnt]-1,linecol);
  }
}


// add next value
void AddValue(uint8_t num,float fval) {
  // not yet defined ???
  num=num%NUM_GRAPHS;
  struct GRAPH *gp=graph[num];
  if (!gp) return;

  if (fval>gp->ymax) fval=gp->ymax;
  if (fval<gp->ymin) fval=gp->ymin;

  int16_t val;
  val=(fval-gp->ymin)/gp->range;

  if (val>gp->ys-1) val=gp->ys-1;
  if (val<0) val=0;

  // summ values
  gp->summ+=val;
  gp->dcnt++;

  // decimation option
  if (gp->decimation<0) {
    if (gp->dcnt>=-gp->decimation) {
      gp->dcnt=0;
      // calc average
      val=gp->summ/-gp->decimation;
      gp->summ=0;
      // add to graph
      AddGraph(num,val);
    }
  }
}
#endif

// get asci float number
uint8_t fatoiv(char *cp,float *res) {
  uint8_t index=0;
  *res=CharToDouble(cp);
  while (*cp) {
    if ((*cp>='0' && *cp<='9') || (*cp=='-') || (*cp=='.')) {
      cp++;
      index++;
    } else {
      break;
    }
  }
  return index;
}

// get asci number until delimiter and return asci number lenght and value
uint8_t atoiv(char *cp, int16_t *res)
{
  uint8_t index = 0;
  *res = atoi(cp);
  while (*cp) {
    if ((*cp>='0' && *cp<='9') || (*cp=='-')) {
      cp++;
      index++;
    } else {
      break;
    }
  }
  return index;
}

// right align string
void alignright(char *string) {
  uint16_t slen=strlen(string);
  uint16_t len=slen;
  while (len) {
    // count spaces to the right
    if (string[len-1]!=' ') {
      break;
    }
    len--;
  }
  uint16_t diff=slen-len;
  if (diff>0) {
    // move string
    memmove(&string[diff],string,len);
    memset(string,' ',diff);
  }
}

#define ESCAPE_CHAR '~'

// decode text escapes, 1 hexbyte assumed
void decode_te(char *line) {
  char sbuf[3],*cp;
  while (*line) {
    if (*line==ESCAPE_CHAR) {
      cp=line+1;
      if (*cp!=0 && *cp==ESCAPE_CHAR) {
        // escape escape, discard one
        memmove(cp,cp+1,strlen(cp));
      } else {
        // escape HH
        if (strlen(cp)<2) {
          // illegal lenght, ignore
          return;
        }
        // take 2 hex chars
        sbuf[0]=*(cp);
        sbuf[1]=*(cp+1);
        sbuf[2]=0;
        *line=strtol(sbuf,0,16);
        // must shift string 2 bytes shift zero also
        memmove(cp,cp+2,strlen(cp)-1);
      }
    }
    line++;
  }
}

/*-------------------------------------------------------------------------------------------*/

#define DISPLAY_BUFFER_COLS    128          // Max number of characters in linebuf

void DisplayText()
{
  uint8_t lpos;
  uint8_t escape = 0;
  uint8_t var;
  int16_t lin = 0;
  int16_t col = 0;
  int16_t fill = 0;
  int16_t temp;
  int16_t temp1;
  float ftemp;

  char linebuf[DISPLAY_BUFFER_COLS];
  char *dp = linebuf;
  char *cp = XdrvMailbox.data;

  memset(linebuf, ' ', sizeof(linebuf));
  linebuf[sizeof(linebuf)-1] = 0;
  *dp = 0;

  //if (!renderer) return;

  while (*cp) {
    if (!escape) {
      // check for escape
      if (*cp == '[') {
        escape = 1;
        cp++;
        // if string in buffer print it
        decode_te(linebuf);
        if ((uint32_t)dp - (uint32_t)linebuf) {
          if (!fill) { *dp = 0; }
          if (fill<0) {
            // right DPIO_FRAMEWORK_ARDUINO_LWIP_HIGHER_BANDWIDTH
            alignright(linebuf);
          }
          if (col > 0 && lin > 0) {
            // use col and lin
            if (!renderer) DisplayDrawStringAt(col, lin, linebuf, fg_color, 1);
            else renderer->DrawStringAt(col, lin, linebuf, fg_color, 1);
          } else {
            // use disp_xpos, disp_ypos
            if (!renderer) DisplayDrawStringAt(disp_xpos, disp_ypos, linebuf, fg_color, 0);
            else renderer->DrawStringAt(disp_xpos, disp_ypos, linebuf, fg_color, 0);
          }
          memset(linebuf, ' ', sizeof(linebuf));
          linebuf[sizeof(linebuf)-1] = 0;
          dp = linebuf;
        }
      } else {
        // copy chars
        if (dp < (linebuf + DISPLAY_BUFFER_COLS)) { *dp++ = *cp++; }
      }
    } else {
      // check escapes
      if (*cp == ']') {
        escape = 0;
        cp++;
      } else {
        // analyze escapes
        switch (*cp++) {
          case 'z':
            // clear display
            if (!renderer) DisplayClear();
            else renderer->fillScreen(bg_color);
            disp_xpos = 0;
            disp_ypos = 0;
            col = 0;
            lin = 0;
            break;
          case 'i':
            // init display with partial update
            DisplayInit(DISPLAY_INIT_PARTIAL);
            break;
          case 'I':
            // init display with full refresh
            DisplayInit(DISPLAY_INIT_FULL);
            break;
          case 'o':
            if (!renderer) DisplayOnOff(0);
            else renderer->DisplayOnff(0);
            break;
          case 'O':
            if (!renderer) DisplayOnOff(1);
            else renderer->DisplayOnff(1);
            break;
          case 'x':
            // set disp_xpos
            var = atoiv(cp, &disp_xpos);
            cp += var;
            break;
          case 'y':
            // set disp_ypos
            var = atoiv(cp, &disp_ypos);
            cp += var;
            break;
          case 'l':
            // text line lxx
            var = atoiv(cp, &lin);
            cp += var;
            //display.setCursor(display.getCursorX(),(lin-1)*font_y*txtsize);
            break;
          case 'c':
            // text column cxx
            var = atoiv(cp, &col);
            cp += var;
            //display.setCursor((col-1)*font_x*txtsize,display.getCursorY());
            break;
          case 'C':
            // fg color cxx
            if (*cp=='i') {
              // color index 0-18
              cp++;
              var = atoiv(cp, &temp);
              if (renderer) ftemp=renderer->GetColorFromIndex(temp);
            } else {
              // float because it must handle unsigned 16 bit
              var = fatoiv(cp,&ftemp);
            }
            fg_color=ftemp;
            cp += var;
            if (renderer) renderer->setTextColor(fg_color,bg_color);
            break;
          case 'B':
              // bg color Bxx
              if (*cp=='i') {
                // color index 0-18
                cp++;
                var = atoiv(cp, &temp);
                if (renderer) ftemp=renderer->GetColorFromIndex(temp);
              } else {
                var = fatoiv(cp,&ftemp);
              }
              bg_color=ftemp;
              cp += var;
              if (renderer) renderer->setTextColor(fg_color,bg_color);
              break;
          case 'p':
            // pad field with spaces fxx, positiv value do left align, negative values right align
            var = atoiv(cp, &fill);
            cp += var;
            linebuf[abs(fill)] = 0;
            break;
          case 'h':
            // hor line to
            var = atoiv(cp, &temp);
            cp += var;
            if (temp < 0) {
              if (renderer) renderer->writeFastHLine(disp_xpos + temp, disp_ypos, -temp, fg_color);
              else DisplayDrawHLine(disp_xpos + temp, disp_ypos, -temp, fg_color);
            } else {
              if (renderer) renderer->writeFastHLine(disp_xpos, disp_ypos, temp, fg_color);
              else DisplayDrawHLine(disp_xpos, disp_ypos, temp, fg_color);
            }
            disp_xpos += temp;
            break;
          case 'v':
            // vert line to
            var = atoiv(cp, &temp);
            cp += var;
            if (temp < 0) {
              if (renderer) renderer->writeFastVLine(disp_xpos, disp_ypos + temp, -temp, fg_color);
              else DisplayDrawVLine(disp_xpos, disp_ypos + temp, -temp, fg_color);
            } else {
              if (renderer) renderer->writeFastVLine(disp_xpos, disp_ypos, temp, fg_color);
              else DisplayDrawVLine(disp_xpos, disp_ypos, temp, fg_color);
            }
            disp_ypos += temp;
            break;
          case 'L':
            // any line to
            var = atoiv(cp, &temp);
            cp += var;
            cp++;
            var = atoiv(cp, &temp1);
            cp += var;
            if (renderer) renderer->writeLine(disp_xpos, disp_ypos, temp, temp1, fg_color);
            else DisplayDrawLine(disp_xpos, disp_ypos, temp, temp1, fg_color);
            disp_xpos = temp;
            disp_ypos = temp1;
            break;
          case 'k':
            // circle
            var = atoiv(cp, &temp);
            cp += var;
            if (renderer) renderer->drawCircle(disp_xpos, disp_ypos, temp, fg_color);
            else DisplayDrawCircle(disp_xpos, disp_ypos, temp, fg_color);
            break;
          case 'K':
            // filled circle
            var = atoiv(cp, &temp);
            cp += var;
            if (renderer) renderer->fillCircle(disp_xpos, disp_ypos, temp, fg_color);
            else DisplayDrawFilledCircle(disp_xpos, disp_ypos, temp, fg_color);
            break;
          case 'r':
            // rectangle
            var = atoiv(cp, &temp);
            cp += var;
            cp++;
            var = atoiv(cp, &temp1);
            cp += var;
            if (renderer) renderer->drawRect(disp_xpos, disp_ypos, temp, temp1, fg_color);
            else DisplayDrawRectangle(disp_xpos, disp_ypos, temp, temp1, fg_color);
            break;
          case 'R':
            // filled rectangle
            var = atoiv(cp, &temp);
            cp += var;
            cp++;
            var = atoiv(cp, &temp1);
            cp += var;
            if (renderer) renderer->fillRect(disp_xpos, disp_ypos, temp, temp1, fg_color);
            else DisplayDrawFilledRectangle(disp_xpos, disp_ypos, temp, temp1, fg_color);
            break;

          case 'u':
            // rounded rectangle
            { int16_t rad;
            var = atoiv(cp, &temp);
            cp += var;
            cp++;
            var = atoiv(cp, &temp1);
            cp += var;
            cp++;
            var = atoiv(cp, &rad);
            cp += var;
            if (renderer) renderer->drawRoundRect(disp_xpos, disp_ypos, temp, temp1, rad, fg_color);
              //else DisplayDrawFilledRectangle(disp_xpos, disp_ypos, temp, temp1, fg_color);
            }
            break;
          case 'U':
            // rounded rectangle
            { int16_t rad;
            var = atoiv(cp, &temp);
            cp += var;
            cp++;
            var = atoiv(cp, &temp1);
            cp += var;
            cp++;
            var = atoiv(cp, &rad);
            cp += var;
            if (renderer) renderer->fillRoundRect(disp_xpos, disp_ypos, temp, temp1, rad, fg_color);
                  //else DisplayDrawFilledRectangle(disp_xpos, disp_ypos, temp, temp1, fg_color);
            }
          case 't':
            // time of day
            if (dp < (linebuf + DISPLAY_BUFFER_COLS) -5) {
              // strange bug => size MUST be 6 otherwise clipped
              snprintf_P(dp, 6, PSTR("%02d" D_HOUR_MINUTE_SEPARATOR "%02d"), RtcTime.hour, RtcTime.minute);
              dp += 5;
            }
            break;
          case 'T':
            // date
            if (dp < (linebuf + DISPLAY_BUFFER_COLS) -8) {
              // strange bug => size MUST be 9 otherwise clipped
              snprintf_P(dp, 9, PSTR("%02d" D_MONTH_DAY_SEPARATOR "%02d" D_YEAR_MONTH_SEPARATOR "%02d"), RtcTime.day_of_month, RtcTime.month, RtcTime.year%2000);
              dp += 8;
            }
            break;
          case 'd':
            // force draw grafics buffer
            if (renderer) renderer->Updateframe();
            else DisplayDrawFrame();
            break;
          case 'D':
            // set auto draw mode
            auto_draw=*cp;
            cp += 1;
            break;
          case 's':
            // size sx
            if (renderer) renderer->setTextSize(*cp&7);
            else DisplaySetSize(*cp&3);
            cp += 1;
            break;
          case 'f':
            // font fx
            if (renderer) renderer->setTextFont(*cp&7);
            else DisplaySetFont(*cp&7);
            cp += 1;
            break;
          case 'a':
            // rotation angle
            if (renderer) renderer->setRotation(*cp&3);
            else DisplaySetRotation(*cp&3);
            cp+=1;
            break;
#ifdef USE_GRAPH
          case 'G':
            // define graph
            { int16_t num,gxp,gyp,gxs,gys,dec,icol;
              float ymin,ymax;
              var=atoiv(cp,&num);
              cp+=var;
              cp++;
              var=atoiv(cp,&gxp);
              cp+=var;
              cp++;
              var=atoiv(cp,&gyp);
              cp+=var;
              cp++;
              var=atoiv(cp,&gxs);
              cp+=var;
              cp++;
              var=atoiv(cp,&gys);
              cp+=var;
              cp++;
              var=atoiv(cp,&dec);
              cp+=var;
              cp++;
              var=fatoiv(cp,&ymin);
              cp+=var;
              cp++;
              var=fatoiv(cp,&ymax);
              cp+=var;
              if (color_type==COLOR_COLOR) {
                // color graph requires channel color
                cp++;
                var=atoiv(cp,&icol);
                cp+=var;
              } else {
                icol=0;
              }
              DefineGraph(num,gxp,gyp,gxs,gys,dec,ymin,ymax,icol);
            }
            break;
          case 'g':
              { float temp;
                int16_t num;
                var=atoiv(cp,&num);
                cp+=var;
                cp++;
                var=fatoiv(cp,&temp);
                cp+=var;
                AddValue(num,temp);
              }
            break;
#endif
#ifdef USE_AWATCH
          case 'w':
              var = atoiv(cp, &temp);
              cp += var;
              DrawAClock(temp);
              break;
#endif

#ifdef USE_TOUCH_BUTTONS
          case 'b':
          { int16_t num,gxp,gyp,gxs,gys,outline,fill,textcolor,textsize;
            var=atoiv(cp,&num);
            cp+=var;
            cp++;
            var=atoiv(cp,&gxp);
            cp+=var;
            cp++;
            var=atoiv(cp,&gyp);
            cp+=var;
            cp++;
            var=atoiv(cp,&gxs);
            cp+=var;
            cp++;
            var=atoiv(cp,&gys);
            cp+=var;
            cp++;
            var=atoiv(cp,&outline);
            cp+=var;
            cp++;
            var=atoiv(cp,&fill);
            cp+=var;
            cp++;
            var=atoiv(cp,&textcolor);
            cp+=var;
            cp++;
            var=atoiv(cp,&textsize);
            cp+=var;
            cp++;
            // text itself
            char bbuff[32];
            uint8_t index=0;
            while (*cp!=':') {
              bbuff[index]=*cp++;
              index++;
              if (index>=sizeof(bbuff)-1) break;
            }
            bbuff[index]=0;
            cp++;
            num=num%MAXBUTTONS;
            if (buttons[num]) {
              delete buttons[num];
            }
            if (renderer) {
              buttons[num]= new Adafruit_GFX_Button();
              if (buttons[num]) buttons[num]->initButtonUL(renderer,gxp,gyp,gxs,gys,renderer->GetColorFromIndex(outline),\
              renderer->GetColorFromIndex(fill),renderer->GetColorFromIndex(textcolor),bbuff,textsize);
              if (buttons[num]) buttons[num]->drawButton(false);
            }
          }
          break;
#endif
          default:
            // unknown escape
            snprintf_P(mqtt_data, sizeof(mqtt_data), PSTR("Unknown Escape"));
            goto exit;
            break;
        }
      }
    }
  }
  exit:
  // now draw buffer
  decode_te(linebuf);
  if ((uint32_t)dp - (uint32_t)linebuf) {
    if (!fill) { *dp = 0; }
    if (fill<0) {
      // right align
      alignright(linebuf);
    }
    if (col > 0 && lin > 0) {
      // use col and lin
      if (!renderer) DisplayDrawStringAt(col, lin, linebuf, fg_color, 1);
      else renderer->DrawStringAt(col, lin, linebuf, fg_color, 1);
    } else {
      // use disp_xpos, disp_ypos
      if (!renderer) DisplayDrawStringAt(disp_xpos, disp_ypos, linebuf, fg_color, 0);
      else renderer->DrawStringAt(disp_xpos, disp_ypos, linebuf, fg_color, 0);
    }
  }
  // draw buffer
  if (auto_draw) {
    if (renderer) renderer->Updateframe();
    else DisplayDrawFrame();
  }
}

/*********************************************************************************************/

#ifdef USE_DISPLAY_MODES1TO5

void DisplayLogBufferIdxInc()
{
  disp_log_buffer_idx++;
  if (DISPLAY_LOG_ROWS == disp_log_buffer_idx) {
    disp_log_buffer_idx = 0;
  }
}

void DisplayLogBufferPtrInc()
{
  disp_log_buffer_ptr++;
  if (DISPLAY_LOG_ROWS == disp_log_buffer_ptr) {
    disp_log_buffer_ptr = 0;
  }
}

/*
void DisplayPrintLog()
{
  disp_refresh--;
  if (!disp_refresh) {
    disp_refresh = Settings.display_refresh;
    disp_log_buffer_active = (disp_log_buffer_idx != disp_log_buffer_ptr);
    if (disp_log_buffer_active) {
      XdspPrintLog(disp_log_buffer[disp_log_buffer_ptr]);
      DisplayLogBufferPtrInc();
    }
  }
}
*/

void DisplayLogBufferInit()
{
  disp_log_buffer_idx = 0;
  disp_log_buffer_ptr = 0;
  disp_log_buffer_active = false;
  disp_refresh = Settings.display_refresh;

  snprintf_P(disp_log_buffer[disp_log_buffer_idx], sizeof(disp_log_buffer[disp_log_buffer_idx]), PSTR(D_VERSION " %s"), my_version);
  DisplayLogBufferIdxInc();
  snprintf_P(disp_log_buffer[disp_log_buffer_idx], sizeof(disp_log_buffer[disp_log_buffer_idx]), PSTR("Display mode %d"), Settings.display_mode);
  DisplayLogBufferIdxInc();
}

/*********************************************************************************************\
 * Sensors
\*********************************************************************************************/

enum SensorQuantity {
  JSON_TEMPERATURE,
  JSON_HUMIDITY, JSON_LIGHT, JSON_NOISE, JSON_AIRQUALITY,
  JSON_PRESSURE, JSON_PRESSUREATSEALEVEL,
  JSON_ILLUMINANCE,
  JSON_GAS,
  JSON_YESTERDAY, JSON_TOTAL, JSON_TODAY,
  JSON_PERIOD,
  JSON_POWERFACTOR, JSON_COUNTER, JSON_ANALOG_INPUT, JSON_UV_LEVEL,
  JSON_CURRENT,
  JSON_VOLTAGE,
  JSON_POWERUSAGE,
  JSON_CO2 };
const char kSensorQuantity[] PROGMEM =
  D_JSON_TEMPERATURE "|"                                                        // degrees
  D_JSON_HUMIDITY "|" D_JSON_LIGHT "|" D_JSON_NOISE "|" D_JSON_AIRQUALITY "|"   // percentage
  D_JSON_PRESSURE "|" D_JSON_PRESSUREATSEALEVEL "|"                             // hPa
  D_JSON_ILLUMINANCE "|"                                                        // lx
  D_JSON_GAS "|"                                                                // kOhm
  D_JSON_YESTERDAY "|" D_JSON_TOTAL "|" D_JSON_TODAY "|"                        // kWh
  D_JSON_PERIOD "|"                                                             // Wh
  D_JSON_POWERFACTOR "|" D_JSON_COUNTER "|" D_JSON_ANALOG_INPUT "|" D_JSON_UV_LEVEL "|"                 // No unit
  D_JSON_CURRENT "|"                                                            // Ampere
  D_JSON_VOLTAGE "|"                                                            // Volt
  D_JSON_POWERUSAGE "|"                                                         // Watt
  D_JSON_CO2 ;                                                                  // ppm

void DisplayJsonValue(const char *topic, const char* device, const char* mkey, const char* value)
{
  char quantity[TOPSZ];
  char spaces[Settings.display_cols[0]];
  char source[Settings.display_cols[0] - Settings.display_cols[1]];
  char svalue[Settings.display_cols[1] +1];

  ShowFreeMem(PSTR("DisplayJsonValue"));

  memset(spaces, 0x20, sizeof(spaces));
  spaces[sizeof(spaces) -1] = '\0';
//  snprintf_P(source, sizeof(source), PSTR("%s/%s%s"), topic, mkey, (DISP_MATRIX == Settings.display_model) ? "" : spaces);  // pow1/Voltage
  snprintf_P(source, sizeof(source), PSTR("%s/%s%s"), topic, mkey, spaces);  // pow1/Voltage

  int quantity_code = GetCommandCode(quantity, sizeof(quantity), mkey, kSensorQuantity);
  if ((-1 == quantity_code) || !strcmp_P(mkey, S_RSLT_POWER)) {  // Ok: Power, Not ok: POWER
    return;
  }
  if (JSON_TEMPERATURE == quantity_code) {
    snprintf_P(svalue, sizeof(svalue), PSTR("%s~%s"), value, disp_temp);
  }
  else if ((quantity_code >= JSON_HUMIDITY) && (quantity_code <= JSON_AIRQUALITY)) {
    snprintf_P(svalue, sizeof(svalue), PSTR("%s%%"), value);
  }
  else if ((quantity_code >= JSON_PRESSURE) && (quantity_code <= JSON_PRESSUREATSEALEVEL)) {
    snprintf_P(svalue, sizeof(svalue), PSTR("%s" D_UNIT_PRESSURE), value);
  }
  else if (JSON_ILLUMINANCE == quantity_code) {
    snprintf_P(svalue, sizeof(svalue), PSTR("%s" D_UNIT_LUX), value);
  }
  else if (JSON_GAS == quantity_code) {
    snprintf_P(svalue, sizeof(svalue), PSTR("%s" D_UNIT_KILOOHM), value);
  }
  else if ((quantity_code >= JSON_YESTERDAY) && (quantity_code <= JSON_TODAY)) {
    snprintf_P(svalue, sizeof(svalue), PSTR("%s" D_UNIT_KILOWATTHOUR), value);
  }
  else if (JSON_PERIOD == quantity_code) {
    snprintf_P(svalue, sizeof(svalue), PSTR("%s" D_UNIT_WATTHOUR), value);
  }
  else if ((quantity_code >= JSON_POWERFACTOR) && (quantity_code <= JSON_UV_LEVEL)) {
    snprintf_P(svalue, sizeof(svalue), PSTR("%s"), value);
  }
  else if (JSON_CURRENT == quantity_code) {
    snprintf_P(svalue, sizeof(svalue), PSTR("%s" D_UNIT_AMPERE), value);
  }
  else if (JSON_VOLTAGE == quantity_code) {
    snprintf_P(svalue, sizeof(svalue), PSTR("%s" D_UNIT_VOLT), value);
  }
  else if (JSON_POWERUSAGE == quantity_code) {
    snprintf_P(svalue, sizeof(svalue), PSTR("%s" D_UNIT_WATT), value);
  }
  else if (JSON_CO2 == quantity_code) {
    snprintf_P(svalue, sizeof(svalue), PSTR("%s" D_UNIT_PARTS_PER_MILLION), value);
  }
  snprintf_P(disp_log_buffer[disp_log_buffer_idx], sizeof(disp_log_buffer[disp_log_buffer_idx]), PSTR("%s %s"), source, svalue);

//  snprintf_P(log_data, sizeof(log_data), PSTR(D_LOG_DEBUG "mkey [%s], source [%s], value [%s], quantity_code %d, log_buffer [%s]"), mkey, source, value, quantity_code, disp_log_buffer[disp_log_buffer_idx]);
//  AddLog(LOG_LEVEL_DEBUG);

  DisplayLogBufferIdxInc();
}

void DisplayAnalyzeJson(char *topic, char *json)
{
// //tele/pow2/STATE    {"Time":"2017-09-20T11:53:03", "Uptime":10, "Vcc":3.123, "POWER":"ON", "Wifi":{"AP":2, "SSId":"indebuurt2", "RSSI":68, "APMac":"00:22:6B:FE:8E:20"}}
// //tele/pow2/ENERGY   {"Time":"2017-09-20T11:53:03", "Total":6.522, "Yesterday":0.150, "Today":0.073, "Period":0.5, "Power":12.1, "Factor":0.56, "Voltage":210.1, "Current":0.102}

// tele/pow1/SENSOR = {"Time":"2018-01-02T17:13:17","ENERGY":{"Total":13.091,"Yesterday":0.060,"Today":0.046,"Period":0.2,"Power":9.8,"Factor":0.49,"Voltage":206.8,"Current":0.096}}
// tele/dual/STATE    {"Time":"2017-09-20T11:53:03","Uptime":25,"Vcc":3.178,"POWER1":"OFF","POWER2":"OFF","Wifi":{"AP":2,"SSId":"indebuurt2","RSSI":100,"APMac":"00:22:6B:FE:8E:20"}}
// tele/sc/SENSOR     {"Time":"2017-09-20T11:53:09","Temperature":24.0,"Humidity":16.0,"Light":30,"Noise":20,"AirQuality":100,"TempUnit":"C"}
// tele/rf1/SENSOR    {"Time":"2017-09-20T11:53:23","BH1750":{"Illuminance":57}}
// tele/wemos5/SENSOR {"Time":"2017-09-20T11:53:53","SHT1X":{"Temperature":20.1,"Humidity":58.9},"HTU21":{"Temperature":20.7,"Humidity":58.5},"BMP280":{"Temperature":21.6,"Pressure":1020.3},"TempUnit":"C"}
// tele/th1/SENSOR    {"Time":"2017-09-20T11:54:48","DS18B20":{"Temperature":49.7},"TempUnit":"C"}

  const char *tempunit;

//  char jsonStr[MESSZ];
//  strlcpy(jsonStr, json, sizeof(jsonStr));  // Save original before destruction by JsonObject
  String jsonStr = json;  // Move from stack to heap to fix watchdogs (20180626)

  StaticJsonBuffer<1024> jsonBuf;
  JsonObject &root = jsonBuf.parseObject(jsonStr);
  if (root.success()) {

    tempunit = root[D_JSON_TEMPERATURE_UNIT];
    if (tempunit) {
      snprintf_P(disp_temp, sizeof(disp_temp), PSTR("%s"), tempunit);
//      snprintf_P(log_data, sizeof(log_data), disp_temp);
//      AddLog(LOG_LEVEL_DEBUG);
    }

    for (JsonObject::iterator it = root.begin(); it != root.end(); ++it) {
      JsonVariant value = it->value;
      if (value.is<JsonObject>()) {
        JsonObject& Object2 = value;
        for (JsonObject::iterator it2 = Object2.begin(); it2 != Object2.end(); ++it2) {
          JsonVariant value2 = it2->value;
          if (value2.is<JsonObject>()) {
            JsonObject& Object3 = value2;
            for (JsonObject::iterator it3 = Object3.begin(); it3 != Object3.end(); ++it3) {
              DisplayJsonValue(topic, it->key, it3->key, it3->value.as<const char*>());  // Sensor 56%
            }
          } else {
            DisplayJsonValue(topic, it->key, it2->key, it2->value.as<const char*>());  // Sensor  56%
          }
        }
      } else {
        DisplayJsonValue(topic, it->key, it->key, it->value.as<const char*>());  // Topic  56%
      }
    }
  }
}

void DisplayMqttSubscribe()
{
/* Subscribe to tele messages only
 * Supports the following FullTopic formats
 * - %prefix%/%topic%
 * - home/%prefix%/%topic%
 * - home/level2/%prefix%/%topic% etc.
 */
//  if (Settings.display_mode &0x04) {
  if (Settings.display_model) {

    char stopic[TOPSZ];
    char ntopic[TOPSZ];

    ntopic[0] = '\0';
    strlcpy(stopic, Settings.mqtt_fulltopic, sizeof(stopic));
    char *tp = strtok(stopic, "/");
    while (tp != NULL) {
      if (!strcmp_P(tp, PSTR(MQTT_TOKEN_PREFIX))) {
        break;
      }
      strncat_P(ntopic, PSTR("+/"), sizeof(ntopic));           // Add single-level wildcards
      tp = strtok(NULL, "/");
    }
    strncat(ntopic, Settings.mqtt_prefix[2], sizeof(ntopic));  // Subscribe to tele messages
    strncat_P(ntopic, PSTR("/#"), sizeof(ntopic));             // Add multi-level wildcard
    MqttSubscribe(ntopic);
    disp_subscribed = 1;
  } else {
    disp_subscribed = 0;
  }
}

boolean DisplayMqttData()
{
  if (disp_subscribed) {
    char stopic[TOPSZ];

    snprintf_P(stopic, sizeof(stopic) , PSTR("%s/"), Settings.mqtt_prefix[2]);  // tele/
    char *tp = strstr(XdrvMailbox.topic, stopic);
    if (tp) {                                                // tele/sonoff/SENSOR
      if (Settings.display_mode &0x04) {
        tp = tp + strlen(stopic);                              // sonoff/SENSOR
        char *topic = strtok(tp, "/");                         // sonoff
        DisplayAnalyzeJson(topic, XdrvMailbox.data);
      }
      return true;
    }
  }
  return false;
}

void DisplayLocalSensor()
{
  if ((Settings.display_mode &0x02) && (0 == tele_period)) {
    DisplayAnalyzeJson(mqtt_topic, mqtt_data);
  }
}

#endif  // USE_DISPLAY_MODES1TO5

/*********************************************************************************************\
 * Public
\*********************************************************************************************/

void DisplayInitDriver()
{

  XdspCall(FUNC_DISPLAY_INIT_DRIVER);

  if (Settings.display_model) {
    devices_present++;
    disp_device = devices_present;

#ifndef USE_DISPLAY_MODES1TO5
    Settings.display_mode = 0;
#else
    snprintf_P(disp_temp, sizeof(disp_temp), PSTR("%c"), TempUnit());
    DisplayLogBufferInit();
#endif  // USE_DISPLAY_MODES1TO5
  }
}


void DisplaySetPower()
{
  disp_power = bitRead(XdrvMailbox.index, disp_device -1);
  if (Settings.display_model) {
    if (!renderer) XdspCall(FUNC_DISPLAY_POWER);
    else renderer->DisplayOnff(disp_power);
  }
}

void DisplayInit(uint8_t mode)
{
  if (renderer)  {
    renderer->DisplayInit(mode,Settings.display_size,Settings.display_rotate,Settings.display_font);
  }
  else {
    dsp_init = mode;
    XdspCall(FUNC_DISPLAY_INIT);
  }
}

void DisplayClear()
{
  XdspCall(FUNC_DISPLAY_CLEAR);
}

void DisplayDrawStringAt(uint16_t x, uint16_t y, char *str, uint16_t fg_color, uint8_t flag)
{
  dsp_x = x;
  dsp_y = y;
  dsp_str = str;
  dsp_color = fg_color;
  dsp_flag = flag;
  XdspCall(FUNC_DISPLAY_DRAW_STRING);
}

void DisplayDrawHLine(uint16_t x, uint16_t y, int16_t len, uint16_t fg_color)
{
  dsp_x = x;
  dsp_y = y;
  dsp_len = len;
  dsp_color = fg_color;
  XdspCall(FUNC_DISPLAY_DRAW_HLINE);
}

void DisplayDrawVLine(uint16_t x, uint16_t y, int16_t len, uint16_t fg_color)
{
  dsp_x = x;
  dsp_y = y;
  dsp_len = len;
  dsp_color = fg_color;
  XdspCall(FUNC_DISPLAY_DRAW_VLINE);
}

void DisplayDrawLine(uint16_t x, uint16_t y, uint16_t x2, uint16_t y2, uint16_t fg_color)
{
  dsp_x = x;
  dsp_y = y;
  dsp_x2 = x2;
  dsp_y2 = y2;
  dsp_color = fg_color;
  XdspCall(FUNC_DISPLAY_DRAW_LINE);
}

void DisplayDrawCircle(uint16_t x, uint16_t y, uint16_t rad, uint16_t fg_color)
{
  dsp_x = x;
  dsp_y = y;
  dsp_rad = rad;
  dsp_color = fg_color;
  XdspCall(FUNC_DISPLAY_DRAW_CIRCLE);
}

void DisplayDrawFilledCircle(uint16_t x, uint16_t y, uint16_t rad, uint16_t fg_color)
{
  dsp_x = x;
  dsp_y = y;
  dsp_rad = rad;
  dsp_color = fg_color;
  XdspCall(FUNC_DISPLAY_FILL_CIRCLE);
}

void DisplayDrawRectangle(uint16_t x, uint16_t y, uint16_t x2, uint16_t y2, uint16_t fg_color)
{
  dsp_x = x;
  dsp_y = y;
  dsp_x2 = x2;
  dsp_y2 = y2;
  dsp_color = fg_color;
  XdspCall(FUNC_DISPLAY_DRAW_RECTANGLE);
}

void DisplayDrawFilledRectangle(uint16_t x, uint16_t y, uint16_t x2, uint16_t y2, uint16_t fg_color)
{
  dsp_x = x;
  dsp_y = y;
  dsp_x2 = x2;
  dsp_y2 = y2;
  dsp_color = fg_color;
  XdspCall(FUNC_DISPLAY_FILL_RECTANGLE);
}

void DisplayDrawFrame()
{
  XdspCall(FUNC_DISPLAY_DRAW_FRAME);
}

void DisplaySetSize(uint8_t size)
{
  Settings.display_size = size &3;
  XdspCall(FUNC_DISPLAY_TEXT_SIZE);
}

void DisplaySetFont(uint8_t font)
{
  Settings.display_font = font &7;
  XdspCall(FUNC_DISPLAY_FONT_SIZE);
}

void DisplaySetRotation(uint8_t rotation)
{
  Settings.display_rotate = rotation &3;
  XdspCall(FUNC_DISPLAY_ROTATION);
}

void DisplayOnOff(uint8_t on)
{
  dsp_on = on;
  XdspCall(FUNC_DISPLAY_ONOFF);
}

/*
void ListAllFound(void) {
  for (byte m=0; m<10; m++) {

  }
snprintf_P(mqtt_data, sizeof(mqtt_data), S_JSON_DISPLAY_COMMAND_NVALUE, command, Settings.display_model);
}
*/
/*********************************************************************************************\
 * Commands
\*********************************************************************************************/

boolean DisplayCommand()
{
  char command [CMDSZ];
  boolean serviced = true;
  uint8_t disp_len = strlen(D_CMND_DISPLAY);  // Prep for string length change

  if (!strncasecmp_P(XdrvMailbox.topic, PSTR(D_CMND_DISPLAY), disp_len)) {  // Prefix
    int command_code = GetCommandCode(command, sizeof(command), XdrvMailbox.topic +disp_len, kDisplayCommands);
    if (-1 == command_code) {
      serviced = false;  // Unknown command
    }
    else if (CMND_DISPLAY == command_code) {
      snprintf_P(mqtt_data, sizeof(mqtt_data), PSTR("{\"" D_CMND_DISPLAY "\":{\"" D_CMND_DISP_MODEL "\":%d,\"" D_CMND_DISP_MODE "\":%d,\"" D_CMND_DISP_DIMMER "\":%d,\""
         D_CMND_DISP_SIZE "\":%d,\"" D_CMND_DISP_FONT "\":%d,\"" D_CMND_DISP_ROTATE "\":%d,\"" D_CMND_DISP_REFRESH "\":%d,\"" D_CMND_DISP_COLS "\":[%d,%d],\"" D_CMND_DISP_ROWS "\":%d}}"),
        Settings.display_model, Settings.display_mode, Settings.display_dimmer, Settings.display_size, Settings.display_font, Settings.display_rotate, Settings.display_refresh,
        Settings.display_cols[0], Settings.display_cols[1], Settings.display_rows);
    }
    else if (CMND_DISP_MODEL == command_code) {
      if ((XdrvMailbox.payload >= 0) && (XdrvMailbox.payload < DISPLAY_MAX_DRIVERS)) {
        uint8_t last_display_model = Settings.display_model;
        Settings.display_model = XdrvMailbox.payload;
        if (XdspCall(FUNC_DISPLAY_MODEL)) {
          restart_flag = 2;  // Restart to re-init interface and add/Remove MQTT subscribe
        } else {
          Settings.display_model = last_display_model;
        }
      }
      // list all models found
      //ListAllFound();
      snprintf_P(mqtt_data, sizeof(mqtt_data), S_JSON_DISPLAY_COMMAND_NVALUE, command, Settings.display_model);
    }
    else if (CMND_DISP_MODE == command_code) {
#ifdef USE_DISPLAY_MODES1TO5
/*     Matrix               LCD / Oled                           TFT
 * 1 = Text up and time     Time
 * 2 = Date                 Local sensors                        Local sensors
 * 3 = Day                  Local sensors and time               Local sensors and time
 * 4 = Mqtt left and time   Mqtt (incl local) sensors            Mqtt (incl local) sensors
 * 5 = Mqtt up and time     Mqtt (incl local) sensors and time   Mqtt (incl local) sensors and time
*/
      if ((XdrvMailbox.payload >= 0) && (XdrvMailbox.payload <= 5)) {
        uint8_t last_display_mode = Settings.display_mode;
        Settings.display_mode = XdrvMailbox.payload;
        if (!disp_subscribed) {
          restart_flag = 2;  // Restart to Add/Remove MQTT subscribe
        } else {
          if (last_display_mode && !Settings.display_mode) {  // Switch to mode 0
            DisplayInit(DISPLAY_INIT_MODE);
            renderer->fillScreen(bg_color);
          }
          if (!last_display_mode && Settings.display_mode) {  // Switch to non mode 0
            DisplayInit(DISPLAY_INIT_MODE);
            DisplayLogBufferInit();
          }
        }
      }
#endif  // USE_DISPLAY_MODES1TO5
      snprintf_P(mqtt_data, sizeof(mqtt_data), S_JSON_DISPLAY_COMMAND_NVALUE, command, Settings.display_mode);
    }
    else if (CMND_DISP_DIMMER == command_code) {
      if ((XdrvMailbox.payload >= 0) && (XdrvMailbox.payload <= 100)) {
        Settings.display_dimmer = ((XdrvMailbox.payload +1) * 100) / 666;  // Correction for Domoticz (0 - 15)
        if (Settings.display_dimmer && !(disp_power)) {
          ExecuteCommandPower(disp_device, POWER_ON, SRC_DISPLAY);
        }
        else if (!Settings.display_dimmer && disp_power) {
          ExecuteCommandPower(disp_device, POWER_OFF, SRC_DISPLAY);
        }
      }
      snprintf_P(mqtt_data, sizeof(mqtt_data), S_JSON_DISPLAY_COMMAND_NVALUE, command, Settings.display_dimmer);
    }
    else if (CMND_DISP_SIZE == command_code) {
      if ((XdrvMailbox.payload > 0) && (XdrvMailbox.payload <= 4)) {
        Settings.display_size = XdrvMailbox.payload;
      }
      snprintf_P(mqtt_data, sizeof(mqtt_data), S_JSON_DISPLAY_COMMAND_NVALUE, command, Settings.display_size);
    }
    else if (CMND_DISP_FONT == command_code) {
      if ((XdrvMailbox.payload >=0) && (XdrvMailbox.payload <= 4)) {
        Settings.display_font = XdrvMailbox.payload;
      }
      snprintf_P(mqtt_data, sizeof(mqtt_data), S_JSON_DISPLAY_COMMAND_NVALUE, command, Settings.display_font);
    }
    else if (CMND_DISP_ROTATE == command_code) {
      if ((XdrvMailbox.payload >= 0) && (XdrvMailbox.payload < 4)) {
        Settings.display_rotate = XdrvMailbox.payload;
        DisplayInit(DISPLAY_INIT_MODE);
      }
      snprintf_P(mqtt_data, sizeof(mqtt_data), S_JSON_DISPLAY_COMMAND_NVALUE, command, Settings.display_rotate);
    }
    else if (CMND_DISP_TEXT == command_code) {
      mqtt_data[0] = '\0';
      if (disp_device && XdrvMailbox.data_len > 0) {
#ifndef USE_DISPLAY_MODES1TO5
        DisplayText();
#else
        if (!Settings.display_mode) {
          DisplayText();
        } else {
          strlcpy(disp_log_buffer[disp_log_buffer_idx], XdrvMailbox.data, sizeof(disp_log_buffer[disp_log_buffer_idx]));
          DisplayLogBufferIdxInc();
        }
#endif  // USE_DISPLAY_MODES1TO5
      } else {
        snprintf_P(mqtt_data, sizeof(mqtt_data), PSTR("No Text"));
      }
      if (mqtt_data[0] == '\0') {
        snprintf_P(mqtt_data, sizeof(mqtt_data), S_JSON_DISPLAY_COMMAND_VALUE, command, XdrvMailbox.data);
      }
    }
    else if ((CMND_DISP_ADDRESS == command_code) && (XdrvMailbox.index > 0) && (XdrvMailbox.index <= 8)) {
      if ((XdrvMailbox.payload >= 0) && (XdrvMailbox.payload <= 255)) {
        Settings.display_address[XdrvMailbox.index -1] = XdrvMailbox.payload;
      }
      snprintf_P(mqtt_data, sizeof(mqtt_data), S_JSON_DISPLAY_COMMAND_INDEX_NVALUE, command, XdrvMailbox.index, Settings.display_address[XdrvMailbox.index -1]);
    }
    else if (CMND_DISP_REFRESH == command_code) {
      if ((XdrvMailbox.payload >= 1) && (XdrvMailbox.payload <= 7)) {
        Settings.display_refresh = XdrvMailbox.payload;
      }
      snprintf_P(mqtt_data, sizeof(mqtt_data), S_JSON_DISPLAY_COMMAND_NVALUE, command, Settings.display_refresh);
    }
    else if ((CMND_DISP_COLS == command_code) && (XdrvMailbox.index > 0) && (XdrvMailbox.index <= 2)) {
      if ((XdrvMailbox.payload > 0) && (XdrvMailbox.payload <= DISPLAY_MAX_COLS)) {
        Settings.display_cols[XdrvMailbox.index -1] = XdrvMailbox.payload;
      }
      snprintf_P(mqtt_data, sizeof(mqtt_data), S_JSON_DISPLAY_COMMAND_INDEX_NVALUE, command, XdrvMailbox.index, Settings.display_cols[XdrvMailbox.index -1]);
    }
    else if (CMND_DISP_ROWS == command_code) {
      if ((XdrvMailbox.payload > 0) && (XdrvMailbox.payload <= DISPLAY_MAX_ROWS)) {
        Settings.display_rows = XdrvMailbox.payload;
      }
      snprintf_P(mqtt_data, sizeof(mqtt_data), S_JSON_DISPLAY_COMMAND_NVALUE, command, Settings.display_rows);
    }
    else serviced = false;  // Unknown command
  }
  else serviced = false;  // Unknown command

  return serviced;
}

/*********************************************************************************************\
 * Interface
\*********************************************************************************************/

#define XDRV_13

boolean Xdrv13(byte function)
{
  boolean result = false;
#ifdef USE_SOFTSPI
  if (XdspPresent()) {
#else
  if ((i2c_flg || spi_flg) && XdspPresent()) {
#endif
    switch (function) {
      case FUNC_PRE_INIT:
        DisplayInitDriver();
        break;
      case FUNC_EVERY_50_MSECOND:
        if (Settings.display_model) { XdspCall(FUNC_DISPLAY_EVERY_50_MSECOND); }
        break;
      case FUNC_COMMAND:
        result = DisplayCommand();
        break;
      case FUNC_SET_POWER:
        DisplaySetPower();
        break;
      case FUNC_EVERY_SECOND:
#ifdef USE_GRAPH
        DisplayCheckGraph();
#endif
#ifdef USE_DISPLAY_MODES1TO5
        if (Settings.display_model && Settings.display_mode) { XdspCall(FUNC_DISPLAY_EVERY_SECOND); }
#endif
        break;
#ifdef USE_DISPLAY_MODES1TO5
      case FUNC_MQTT_SUBSCRIBE:
        DisplayMqttSubscribe();
        break;
      case FUNC_MQTT_DATA:
        result = DisplayMqttData();
        break;
      case FUNC_SHOW_SENSOR:
        DisplayLocalSensor();
        break;
#endif // USE_DISPLAY_MODES1TO5
    }
  }
  return result;
}

#endif  // USE_DISPLAY
#endif  // USE_I2C or USE_SPI

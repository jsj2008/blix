
#ifndef ENGINE_TEXT_H
#define ENGINE_TEXT_H

#include "common.h"
#include "DisplayObject.h"
#include "SkPaint.h"

class ShaderProgram;
class SkCanvas;

class _Typeface;

/**
 * Although it shares a name with flash.display.TextField, our TextField
 * does not share much of the same interface or functionality.
 *
 * Flash text rendering is extremely complex, full of quirks from old flash
 * versions, and has a bulky API. For now, we have a simple, lightweight
 * interface, although it is lacking in advanced functionality.
 */
class TextField : public DisplayObject
{
public:

    enum Align {
        ALIGN_LEFT   = SkPaint::kLeft_Align,
        ALIGN_CENTER = SkPaint::kCenter_Align,
        ALIGN_RIGHT  = SkPaint::kRight_Align
    };

    /**
     * @param face the name of a truetype text file in assets to use.
     *        Files are cached and not reloaded in each new TextField instance.
     *
     * @param size Text point size.
     */
    TextField(const std::string& face, uint size = 12);
    ~TextField();

    inline const std::string& text() const { return _str; }
    void text(const std::string& s);

    void color(uint color);

    void size(uint size);
    inline uint size() { return _paint.getTextSize(); }

    void setAntialias(bool aa);

    void align(Align align);
    inline Align align() { return (Align)_paint.getTextAlign(); }

protected:

    void _draw(Canvas * canvas);

private:

    void _remeasure();

    _Typeface * _typeface;
    std::string _str;
    SkPaint _paint;
    float _offsetX;
    float _offsetY;
};

#endif

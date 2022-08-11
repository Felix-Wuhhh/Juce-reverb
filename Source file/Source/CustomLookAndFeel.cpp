
#include <JuceHeader.h>
#include "CustomLookAndFeel.h"

CustomLookAndFeel::CustomLookAndFeel(){};
CustomLookAndFeel::~CustomLookAndFeel(){};

juce::Slider::SliderLayout CustomLookAndFeel::getSliderLayout (juce::Slider& slider)
//Slider布局
{
    auto localBounds = slider.getLocalBounds(); //localBounds
    
    juce::Slider::SliderLayout layout; //创建一个layout
    
    layout.textBoxBounds = localBounds; //textbox界限
    layout.sliderBounds = localBounds; //slider界限

    return layout; //返回layout
}

void CustomLookAndFeel::drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
                                          const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider& slider)
//绘制rotary slider
{
    auto fill = slider.findColour (juce::Slider::rotarySliderFillColourId);
    //For rotary sliders, this colour fills the outer curve.

    auto bounds = juce::Rectangle<float> (x, y, width, height).reduced (2.0f);
    //一个方形边界，起始点（左上顶点）、长宽。再减去2？
    
    auto radius = juce::jmin (bounds.getWidth(), bounds.getHeight()) / 2.0f;
    //jim: 返回两个值中较小的那个值。
    //取边界的宽度和长度一半中的较小值。
    
    auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    //toAngle等于旋转开始角度加上slider位置乘上旋转结束角度减去旋转开始角度
    
    auto lineW = radius * 0.085f;
    //半径乘上0.085，这是啥？？
    
    auto arcRadius = radius - lineW * 1.5f;
    //圆弧半径，阿巴阿巴
    
    juce::Path backgroundArc; //背景圆弧，那个灰色的？
    
    backgroundArc.addCentredArc (bounds.getCentreX(),
                                 bounds.getCentreY(),
                                 arcRadius,
                                 arcRadius,
                                 0.0f,
                                 rotaryStartAngle,
                                 rotaryEndAngle,
                                 true);
    
    g.setColour (blackGrey); //哦，看来就是灰色那部分
    g.strokePath (backgroundArc, juce::PathStrokeType (lineW, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
    //stroke部分
    
    juce::Path valueArc;
    //弧度的值？有点意思
    valueArc.addCentredArc (bounds.getCentreX(),
                            bounds.getCentreY(),
                            arcRadius,
                            arcRadius,
                            0.0f,
                            rotaryStartAngle,
                            toAngle,
                            true);
        
    auto alpha = 0.1f + (float) slider.getValue() * 0.9f;
    //
    auto brightness = 0.4f + (float) slider.getValue() * 0.6f;
    //明暗度

    g.setColour (fill.withAlpha (alpha).brighter (brightness));
    //fill定义在前面，应该就是颜色，貌似这句话就是设置颜色的明暗度
    
    g.strokePath (valueArc, juce::PathStrokeType (lineW, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
    //重复了？？上面不是刚写过这句话嘛
    
    auto thumbWidth = lineW * 2.0f;
    //这个thumb好像就是突出来的那个像指针一样的东西
    juce::Path thumb;
    thumb.addRectangle (-thumbWidth / 2, -thumbWidth / 2, thumbWidth, radius + lineW);
    
    g.setColour (offWhite);
    g.fillPath (thumb, juce::AffineTransform::rotation (toAngle + 3.12f).translated (bounds.getCentre()));

    g.fillEllipse (bounds.reduced (8.0f));
}

juce::Label* CustomLookAndFeel::createSliderTextBox (juce::Slider& slider)
{
    auto* l = new juce::Label();
    l->setJustificationType (juce::Justification::centred);
    l->setColour (juce::Label::textColourId, slider.findColour (juce::Slider::textBoxTextColourId));
    l->setColour (juce::Label::textWhenEditingColourId, slider.findColour (juce::Slider::textBoxTextColourId));
    l->setColour (juce::Label::outlineWhenEditingColourId, slider.findColour (juce::Slider::textBoxOutlineColourId));
    l->setInterceptsMouseClicks (false, false);
    l->setFont (15);
    
    return l;
}

juce::Font CustomLookAndFeel::getTextButtonFont (juce::TextButton&, int buttonHeight)
{
    juce::Font font ("Avenir Next Medium", 90.f, 0);
    return { font };
}

void CustomLookAndFeel::drawButtonBackground (juce::Graphics& g, juce::Button& button, const juce::Colour& backgroundColour,
                                              bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
}

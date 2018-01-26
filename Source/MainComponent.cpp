#include "../JuceLibraryCode/JuceHeader.h"
#include "ADSR.h"

class MainContentComponent   : public AudioAppComponent, public Slider::Listener, public TextButton::Listener
{
public:
    //==============================================================================
    MainContentComponent()
    {
        setSize (800, 600);
        isDist = false;

        //Specify the number of input and output channels to open
        setAudioChannels (2, 2);
        
        //Set look and feel
        masterLookAndFeel.setColour(Slider::thumbColourId, Colours::darkseagreen);
        envelopeLookAndFeel.setColour(Slider::thumbColourId, Colours::indianred);
        
        //Lots of magic numbers here because the values are basically arbitrary
        //Master Volume
        addAndMakeVisible(allVol);
        allVol.setLookAndFeel(&masterLookAndFeel);
        allVol.setSliderStyle(Slider::Rotary);
        allVol.setTextBoxStyle (Slider::TextBoxBelow, false, 0, 0);
        allVol.setSkewFactor(2);
        allVol.setRange(-96,6);
        allVol.setValue(-6);
        allVol.addListener(this);
        
        //Master Frequency
        addAndMakeVisible(allFreqSlider);
        allFreqSlider.setLookAndFeel(&masterLookAndFeel);
        allFreqSlider.setRange(-9,30);
        allFreqSlider.setValue(0);
        allFreqSlider.addListener(this);
        allFreqSlider.setTextBoxStyle(Slider::NoTextBox, false, 160, aFreqSlider.getTextBoxHeight());
        
        //Voice A
        addAndMakeVisible(aVol);
        aVol.setSliderStyle(Slider::Rotary);
        aVol.setTextBoxStyle (Slider::TextBoxBelow, false, 0, 0);
        aVol.setRange(-96,6);
        aVol.setSkewFactor(2);
        aVol.setValue(-2);
        aVol.addListener(this);

        addAndMakeVisible(aFreqSlider);
        aFreqSlider.setRange(1,6,1);
        aFreqSlider.setValue(2);
        aFreqSlider.addListener(this);
        aFreqSlider.setTextBoxStyle(Slider::NoTextBox, false, 160, aFreqSlider.getTextBoxHeight());
        
        //Voice B
        addAndMakeVisible(bVol);
        bVol.setSliderStyle(Slider::Rotary);
        bVol.setTextBoxStyle (Slider::TextBoxBelow, false, 0, 0);
        aVol.setSkewFactor(2);
        bVol.setRange(-96,6);
        bVol.setValue(-6);
        bVol.addListener(this);
        
        addAndMakeVisible(bFreqSlider);
        bFreqSlider.setRange(1,6,1);
        bFreqSlider.setValue(5);
        bFreqSlider.addListener(this);
        bFreqSlider.setTextBoxStyle(Slider::NoTextBox, false, 160, bFreqSlider.getTextBoxHeight());
        
        
        //Voice C
        addAndMakeVisible(cVol);
        cVol.setSliderStyle(Slider::Rotary);
        cVol.setTextBoxStyle (Slider::TextBoxBelow, false, 0, 0);
        cVol.setSkewFactor(2);
        cVol.setRange(-96,6);
        cVol.setValue(-6);
        cVol.addListener(this);
        
        addAndMakeVisible(cFreqSlider);
        cFreqSlider.setRange(1,6,1);
        cFreqSlider.setValue(2);
        cFreqSlider.addListener(this);
        cFreqSlider.setTextBoxStyle(Slider::NoTextBox, false, 160, aFreqSlider.getTextBoxHeight());
        
        
        //Voice D
        addAndMakeVisible(dVol);
        dVol.setSliderStyle(Slider::Rotary);
        dVol.setTextBoxStyle (Slider::TextBoxBelow, false, 0, 0);
        dVol.setSkewFactor(2);
        dVol.setRange(-96,6);
        dVol.setValue(-12);
        dVol.addListener(this);
        
        addAndMakeVisible(dFreqSlider);
        dFreqSlider.setRange(1,6,1);
        dFreqSlider.setValue(3);
        dFreqSlider.addListener(this);
        dFreqSlider.setTextBoxStyle(Slider::NoTextBox, false, 160, dFreqSlider.getTextBoxHeight());
        
        //Buttons
        addAndMakeVisible(dist);
        dist.setButtonText("Dist");
        dist.addListener(this);
        dist.setEnabled(true);
        
        addAndMakeVisible(mute);
        mute.setButtonText("Mute");
        mute.addListener(this);
        mute.setEnabled(true);
        
        addAndMakeVisible(trem);
        trem.setButtonText("Trem");
        trem.addListener(this);
        trem.setEnabled(true);
        
        //Trem
        addAndMakeVisible(tremRate);
        tremRate.setLookAndFeel(&envelopeLookAndFeel);
        tremRate.setSliderStyle(Slider::LinearVertical);
        tremRate.setSkewFactor(0.25);
        tremRate.setTextBoxStyle (Slider::NoTextBox, false, 0, 0);
        tremRate.setRange(0.03,0.75);
        tremRate.setValue(tremTime);
        tremRate.addListener(this);
        
        //Drive
        addAndMakeVisible(driveLevel);
        driveLevel.setLookAndFeel(&envelopeLookAndFeel);
        driveLevel.setSliderStyle(Slider::LinearVertical);
        driveLevel.setTextBoxStyle (Slider::NoTextBox, false, 0, 0);
        driveLevel.setRange(0.5,4);
        driveLevel.setValue(drive);
        driveLevel.addListener(this);
        
        
        //ADSR Envelope
        addAndMakeVisible(envelope);
        envelope.setButtonText("Env");
        envelope.addListener(this);
        envelope.setEnabled(true);
        
        addAndMakeVisible(envA);
        envA.setLookAndFeel(&envelopeLookAndFeel);
        envA.setSliderStyle(Slider::LinearVertical);
        envA.setTextBoxStyle (Slider::NoTextBox, false, 0, 0);
        envA.setRange(0,10);
        envA.setValue(1);
        envA.addListener(this);
        
        addAndMakeVisible(envD);
        envD.setLookAndFeel(&envelopeLookAndFeel);
        envD.setSliderStyle(Slider::LinearVertical);
        envD.setTextBoxStyle (Slider::NoTextBox, false, 0, 0);
        envD.setRange(0,10);
        envD.setValue(1);
        envD.addListener(this);
        
        addAndMakeVisible(envS);
        envS.setLookAndFeel(&envelopeLookAndFeel);
        envS.setSliderStyle(Slider::LinearVertical);
        envS.setTextBoxStyle (Slider::NoTextBox, false, 0, 0);
        envS.setRange(0,10);
        envS.setValue(1);
        envS.addListener(this);

        addAndMakeVisible(envR);
        envR.setLookAndFeel(&envelopeLookAndFeel);
        envR.setSliderStyle(Slider::LinearVertical);
        envR.setTextBoxStyle (Slider::NoTextBox, false, 0, 0);
        envR.setRange(0,10);
        envR.setValue(1);
        envR.addListener(this);
    }

    ~MainContentComponent()
    {
        shutdownAudio();
    }

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override
    {
        // This function will be called when the audio device is started, or when
        // its settings (i.e. sample rate, block size, etc) are changed.
        
        //initialize sine function values
        amplitude = 0.5;
        aAmplitude = 0.5;
        bAmplitude = 0.5;
        cAmplitude = 0.5;
        dAmplitude = 0.5;
        aFrequency = 77.78;
        bFrequency = 138.59;
        cFrequency = 277.18;
        dFrequency = 554.37;
        frequency = 0;
        aPhase = 0.0;
        bPhase = 0.0;
        cPhase = 0.0;
        dPhase = 0.0;
        time = 0.0;
        deltaTime = 1/sampleRate;
        drive = 1.5;
        tremTime = 0.1;
        
        attackRate = 10*sampleRate;
        decayRate = 30*sampleRate;
        releaseRate = 50*sampleRate;
        sustainLevel = 100;
        // For more details, see the help for AudioProcessor::prepareToPlay()
    }

    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override
    {
        // For more details, see the help for AudioProcessor::getNextAudioBlock()
        if(time >=tremTime){
            time = 0.0;
            isTrem = !isTrem;
        }
        
        float *outputBuffer = new float[bufferToFill.numSamples];
        
        //generate four sine waves
        for(int sample = 0; sample < bufferToFill.numSamples; ++sample) {
            float aVal;
            float bVal;
            float cVal;
            float dVal;
            
            aPhase+=2*double_Pi*(aFrequency+frequency)*deltaTime;
            aVal = aAmplitude * sin(aPhase);
            bPhase+=2*double_Pi*(bFrequency+frequency)*deltaTime;
            bVal = bAmplitude * sin(bPhase);
            cPhase+=2*double_Pi*(cFrequency+frequency)*deltaTime;
            cVal = cAmplitude * sin(cPhase);
            dPhase+=2*double_Pi*(dFrequency+frequency)*deltaTime;
            dVal = dAmplitude * sin(dPhase);
            
            env->setAttackRate(attackRate);
            env->setDecayRate(decayRate);
            env->setReleaseRate(releaseRate);
            env->setSustainLevel(sustainLevel);
            
            outputBuffer[sample] = (aVal+bVal+cVal+dVal)*amplitude;
            
            if(isDist) {
                amplitude=exp(-0.3*drive);
                outputBuffer[sample] = (((sqrt(outputBuffer[sample]) - outputBuffer[sample]) * drive) + outputBuffer[sample])  *  (1 - ((drive / 4) * 5));
            }
            if(isEnvelope) {
                env->gate(true);
                outputBuffer[sample] = outputBuffer[sample] * env->process();
            }
            else{
                env->gate(false);
            }
            if(isMute || (isTremActive && isTrem)) {
                outputBuffer[sample] = outputBuffer[sample]*0;
            }
            outputBuffer[sample] = outputBuffer[sample]*amplitude;
            time+=deltaTime;
            
        }
        
        //iterate over output channels
        for(int channel=0; channel<bufferToFill.buffer->getNumChannels(); ++channel) {
            
            //get a pointer to the start sample in the buffer for this audio channel
            float* const buffer = bufferToFill.buffer->getWritePointer(channel, bufferToFill.startSample);
            
            for(int sample =0; sample < bufferToFill.numSamples; ++sample) {
                buffer[sample] = outputBuffer[sample];
            }
        }
    }
    
    void sliderValueChanged(Slider *slider) override
    {
        //Volumes
        if(slider == &allVol) {
            amplitude = pow(10, ((float)allVol.getValue() / 20.0));
        }
        if(slider == &aVol) {
            aAmplitude = pow(10, ((float)aVol.getValue() / 20.0));
        }
        if(slider == &bVol) {
            bAmplitude = pow(10, ((float)bVol.getValue() / 20.0));
        }
        if(slider == &cVol) {
            cAmplitude = pow(10, ((float)cVol.getValue() / 20.0));
        }
        if(slider == &dVol) {
            dAmplitude = pow(10, ((float)dVol.getValue() / 20.0));
        }
        
        
        //Frequencies
        if(slider == &allFreqSlider) {
            frequency = 10*(float)allFreqSlider.getValue();
            allFreqLabel.setText(std::to_string(frequency)+" Hz", dontSendNotification);
        }
        if(slider == &aFreqSlider) {
            //this should snap the frequency to pentatonic notes
            float aCoeff = 60.103;
            float aPow = 0.1369;
            aFrequency = aCoeff*exp(aPow*(float)aFreqSlider.getValue());
            aFreqLabel.setText(std::to_string(aFrequency)+" Hz", dontSendNotification);
        }
        if(slider == &bFreqSlider) {
            float bCoeff = 120.19;
            float bPow = 0.137;
            bFrequency = bCoeff*exp(bPow*(float)bFreqSlider.getValue());
            bFreqLabel.setText(std::to_string(bFrequency)+" Hz", dontSendNotification);
        }
        if(slider == &cFreqSlider) {
            float cCoeff = 240.37;
            float cPow = 0.137;
            cFrequency = cCoeff*exp(cPow*(float)cFreqSlider.getValue());
            cFreqLabel.setText(std::to_string(cFrequency)+" Hz", dontSendNotification);
        }
        if(slider == &dFreqSlider) {
            float dCoeff = 480.75;
            float dPow = 0.137;
            dFrequency = dCoeff*exp(dPow*(float)dFreqSlider.getValue());
            dFreqLabel.setText(std::to_string(dFrequency)+" Hz", dontSendNotification);
        }
        
        //Envelope
        if(slider == &envA) {
            env->setAttackRate(attackRate*envA.getValue());
        }
        if(slider == &envD) {
            env->setDecayRate(decayRate*envD.getValue());
        }
        if(slider == &envS) {
            env->setSustainLevel(sustainLevel*envS.getValue());
        }
        if(slider == &envR) {
            env->setReleaseRate(envR.getValue());
        }
        
        //Tremolo
        if(slider == &tremRate) {
            tremTime = tremRate.getValue();
        }
        //Drive
        if(slider == &driveLevel) {
            drive = driveLevel.getValue();
        }
        
    }
    
    void buttonClicked(Button* button) override
    {
        if(button == &dist) {
            isDist = !isDist;
            if(isDist){
                dist.setColour(0x1000100, Colour::Colour(255,255,255));
                dist.setColour(0x1000102, Colour::Colour(0,0,0));
            }
            if(!isDist){
                dist.setColour(0x1000100, getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
                dist.setColour(0x1000102, Colour::Colour(255,255,255));
            }
        }
        if(button == &envelope) {
            isEnvelope = !isEnvelope;
            if(isEnvelope){
                envelope.setColour(0x1000100, Colour::Colour(255,255,255));
                envelope.setColour(0x1000102, Colour::Colour(0,0,0));
            }
            if(!isEnvelope){
                envelope.setColour(0x1000100, getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
                envelope.setColour(0x1000102, Colour::Colour(255,255,255));
            }
        }
        if(button == &mute) {
            isMute = !isMute;
            if(isMute){
                mute.setColour(0x1000100, Colour::Colour(255,255,255));
                mute.setColour(0x1000102, Colour::Colour(0,0,0));
            }
            if(!isMute){
                mute.setColour(0x1000100, getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
                mute.setColour(0x1000102, Colour::Colour(255,255,255));
            }
        }
        if(button == &trem) {
            isTremActive = !isTremActive;
            if(isTremActive){
                trem.setColour(0x1000100, Colour::Colour(255,255,255));
                trem.setColour(0x1000102, Colour::Colour(0,0,0));
            }
            if(!isTremActive){
                trem.setColour(0x1000100, getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
                trem.setColour(0x1000102, Colour::Colour(255,255,255));
            }
        }
    }

    void releaseResources() override
    {
        // This will be called when the audio device stops, or when it is being
        // restarted due to a setting change.

        // For more details, see the help for AudioProcessor::releaseResources()
    }

    //==============================================================================
    void paint (Graphics& g) override
    {
        const int border = 100;
        // (Our component is opaque, so we must completely fill the background with a solid colour)
        g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
        g.setFont(Font("Sans Serif", 50.0, Font::bold | Font::italic));
        g.setColour(Colours::white);
        g.drawText("Pop", getWidth()/2, border/3, 3*border, border/2, true);
        g.setFont(Font("Sans Serif", 20.0, Font::bold | Font::italic));
 
        g.drawText("A", border*8/5, border*9/10, 3*border, border/2, true);
        g.drawText("D", border*11/5, border*9/10, 3*border, border/2, true);
        g.drawText("S", border*14/5, border*9/10, 3*border, border/2, true);
        g.drawText("R", border*17/5, border*9/10, 3*border, border/2, true);
    }

    void resized() override
    {
        //TODO: clean up this spaghetti later
        const int freqSliderLeft = 150;
        const int buttonHeight = 50;
        const int xBorder = 20;
        const int yBorder = 100;
        const int rollerSize = 100;
        
        Rectangle<int> area = getLocalBounds();
        allVol.setBounds(xBorder,yBorder, rollerSize, rollerSize);
        aVol.setBounds(xBorder, yBorder+rollerSize, rollerSize, rollerSize);
        bVol.setBounds(xBorder, yBorder+2*rollerSize, rollerSize, rollerSize);
        cVol.setBounds(xBorder, yBorder+3*rollerSize, rollerSize, rollerSize);
        dVol.setBounds(xBorder, yBorder+4*rollerSize, rollerSize, rollerSize);
        
        dist.setBounds(getWidth()*17/20, yBorder/3, getWidth()/8, buttonHeight);
        trem.setBounds(getWidth()*15/20, yBorder/3, getWidth()/8, buttonHeight);
        mute.setBounds(getWidth()*13/20, yBorder/3, getWidth()/8, buttonHeight);
        
        envelope.setBounds(xBorder, yBorder/3, getWidth()/8, buttonHeight);
        
        envA.setBounds(6*xBorder, yBorder/4, getWidth()/8, 1.5*buttonHeight);
        envD.setBounds(9*xBorder, yBorder/4, getWidth()/8, 1.5*buttonHeight);
        envS.setBounds(12*xBorder, yBorder/4, getWidth()/8, 1.5*buttonHeight);
        envR.setBounds(15*xBorder, yBorder/4, getWidth()/8, 1.5*buttonHeight);
        
        allFreqSlider.setBounds(freqSliderLeft, yBorder+(rollerSize/4), getWidth() - freqSliderLeft - 10*xBorder, buttonHeight);
        aFreqSlider.setBounds(freqSliderLeft, (yBorder+8*rollerSize)/4, getWidth() - freqSliderLeft - 10*xBorder, buttonHeight);
        bFreqSlider.setBounds(freqSliderLeft, (yBorder+12*rollerSize)/4, getWidth() - freqSliderLeft - 10*xBorder, buttonHeight);
        cFreqSlider.setBounds(freqSliderLeft, (yBorder+16*rollerSize)/4, getWidth() - freqSliderLeft - 10*xBorder, buttonHeight);
        dFreqSlider.setBounds(freqSliderLeft, (yBorder+20*rollerSize)/4, getWidth() - freqSliderLeft - 10*xBorder, buttonHeight);
        tremRate.setBounds(getWidth()-8.5*xBorder, 1.2*yBorder, buttonHeight, getHeight()-1.5*yBorder);
        driveLevel.setBounds(getWidth()-4.5*xBorder, 1.2*yBorder, buttonHeight, getHeight()-1.5*yBorder);
    }


private:
    //==============================================================================
    LookAndFeel_V4 masterLookAndFeel;
    LookAndFeel_V4 envelopeLookAndFeel;

    float amplitude;
    float aAmplitude;
    float bAmplitude;
    float cAmplitude;
    float dAmplitude;
    
    float aFrequency;
    float bFrequency;
    float cFrequency;
    float dFrequency;
    float frequency;
    
    float aPhase;
    float bPhase;
    float cPhase;
    float dPhase;
    
    float time;
    float deltaTime;
    float tremTime;
    bool isTrem;
    
    float attackRate;
    float decayRate;
    float releaseRate;
    float sustainLevel;
    
    
    Slider aFreqSlider;
    Slider bFreqSlider;
    Slider cFreqSlider;
    Slider dFreqSlider;
    Slider allFreqSlider;
    
    Slider envA;
    Slider envD;
    Slider envS;
    Slider envR;
    Slider tremRate;
    Slider driveLevel;
    
    Label aFreqLabel;
    Label bFreqLabel;
    Label cFreqLabel;
    Label dFreqLabel;
    Label allFreqLabel;
    
    Slider aVol;
    Slider bVol;
    Slider cVol;
    Slider dVol;
    Slider allVol;
    
    TextButton dist;
    bool isDist;
    float drive;
    
    TextButton envelope;
    bool isEnvelope;
    
    TextButton mute;
    bool isMute;
    
    TextButton trem;
    bool isTremActive;
    
    ADSR *env = new ADSR();
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


// (This function is called by the app startup code to create our main component)
Component* createMainContentComponent()     { return new MainContentComponent(); }

 Pop
 
 ![pop](https://github.com/dallinw/Pop/blob/master/pop.png)
 
Pop is a polyphonic, pentatonic synthesizer. It modulates four sine waves along a
set of exponential functions to follow the notes of the pentatonic scale. Each of its
four voices has a one octave range. A master frequency and volume control are
included in addition to individual controls for each voice. It also features a distortion
with adjustable drive level and tremolo with adjustable rate.
 
The ADSR envelope is included in the GUI but not yet fully implemented. Most of its
current code (ADSR.h and ADSR.cpp) comes from Nigel Redmon at <a href="earlevel.com">earlevel.com</a>.
Any code outside of MainComponent.cpp and Main.cpp comes from Juce.

Future possibilities for Pop include:
<ul>
<li>Fixing the ADSR envelope</li>
<li>VST/AU versions for cross-platform use</li>
<li>Adding a cutoff adjustment</li>
<li>Adding reverb</li>
<li>Adding square, sawtooth, and/or triangle waves</li>
<li>Cleaning up some of the uglier parts of this code :D</li>
</ul>

#!/bin/bash

# Clones dependencies
# !Run this script from the Mumm project root!

# create new addons dir?
# mkdir addons
cd ../../addons

# passing no arguments means read only
if [ -z $1 ]; then
    CLONE="git clone https://github.com/"
    echo "Cloning read-only"
else
    CLONE="git clone git@github.com:"
    echo "Cloning writable"
fi

# git clone specific revision of the addons
${CLONE}braitsch/ofxDatGui
${CLONE}arturoc/ofxTween
${CLONE}bakercp/ofxMaps
${CLONE}jefftimesten/ofxJSON
${CLONE}patriciogonzalezvivo/ofxGlmTools
# ${CLONE}tangrams/ofxVectorTile
${CLONE}jeonghopark/ofxVectorTile
${CLONE}memo/ofxMSAInteractiveObject
# cd ofxVectorTile
# git checkout ???
# cd ..


# final step is to cd back to the start dir
cd ../apps/FocusAndContext
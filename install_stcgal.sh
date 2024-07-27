# Set python's version here
PYTHON=python3.11

echo "Installing stcgal..."
[ -d "./stcgal-pyenv" ] && echo -n -e "[ ] removing stcgal...   \r" && rm -r "./stcgal-pyenv"
[ -L "./stcgal" ] && rm -r ./stcgal
echo "[*] stcgal removed      "
python3 -m virtualenv --python=$PYTHON "stcgal-pyenv" || (echo "[!] Couldn't create python virtualenv for stcgal" && exit)
echo "[*] Created python virtualenv for stcgal"
./stcgal-pyenv/bin/pip install stcgal || (echo "[!] Couldn't install stcgal" && exit)
echo "[*] stcgal installation successful"
ln -r -s stcgal-pyenv/bin/stcgal ./stcgal || exit
echo "[*] stcgal shortcut created"
echo $(./stcgal -V)

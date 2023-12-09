echo "Installing stcgal..."
[ -d "./stcgal-pyenv" ] && echo "[ ] removing stcgal..." && rm -r "./stcgal-pyenv"
[ -L "./stcgal" ] && rm -rv ./stcgal
echo "[*] stcgal removed"
python3.10 -m virtualenv --python=python3.10 "stcgal-pyenv" || (echo "[!] Couldn't create python virtualenv for stcgal" && exit)
echo "[*] Created python virtualenv for stcgal"
./stcgal-pyenv/bin/pip install stcgal || (echo "[!] Couldn't install stcgal" && exit)
echo "[*] stcgal installation successful"
ln -s `pwd`/stcgal-pyenv/bin/stcgal ./stcgal || exit
echo "[*] stcgal shortcut created"
echo `./stcgal -V`

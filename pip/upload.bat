conda activate torch36
python setup.py sdist bdist_wheel
python -m twine upload --repository-url https://test.pypi.org/legacy/ dist/*

python -m twine upload dist/*

ktang
IOU

conda activate cyber36
python -m pip install --index-url https://test.pypi.org/simple/ --no-deps qip2>=1.0.0.2

python -m pip install qip2

pip uninstall qip2


import setuptools

with open("README.md", "r") as fh:
    long_description = fh.read()

setuptools.setup(
    name="qip2",
    version="1.0.0.2",
    author="Kim Kuen Tang",
    author_email="kimktang@gmail.com",
    description="Integrate kdb+ into python",
    long_description=long_description,
    long_description_content_type="text/markdown",
    url="https://bitbucket.org/kuentang/pykdb/src/master",
    packages=['qip2'],
    data_files=[('lib\\site-packages\\qip2',["qip2\\qip.pyd","qip2\\boost_numpy36-vc142-mt-x64-1_70.dll","qip2\\boost_python36-vc142-mt-x64-1_70.dll"])],
    classifiers=[
        "Programming Language :: Python :: 3",
        "License :: OSI Approved :: MIT License",
        "Operating System :: Microsoft :: Windows :: Windows 10"
    ],
)
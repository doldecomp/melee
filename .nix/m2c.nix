{
  stdenv,
  buildPythonPackage,
  fetchFromGitHub,

  graphviz,
  poetry-core,
  pycparser,
}:

buildPythonPackage {
  pname = "m2c";
  version = "unstable";

  src = fetchFromGitHub {
    owner = "matt-kempster";
    repo = "m2c";
    rev = "4caccf86a027bf52b9132a8ae9331cb3210305a8";
    hash = "sha256-dutmRYEP1XQwnbrG3d/VZdldl4x+pWxq84aj1xTKApI=";
  };

  postPatch = ''
    substituteInPlace pyproject.toml \
      --replace-fail 'graphviz = "^0.20.1"' ""
  '';

  pyproject = true;

  propagatedBuildInputs = [
    graphviz
    poetry-core
    pycparser
  ];
}

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
    rev = "900b0b6a55307f6cd1270023f641c7380083d8c7";
    hash = "";
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

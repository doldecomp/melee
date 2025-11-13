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
    rev = "f201e8861ba0143676f3078d7354d2f7255555b3";
    hash = "sha256-WhXIeeiRLDeVSgbIuCAlJVTLHtFbJGsM+ACmhsAPUvk=";
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

{
  stdenv,
  buildPythonPackage,
  fetchFromGitHub,
  poetry-core,
  pycparser,
}:

buildPythonPackage {
  name = "m2c";

  src = fetchFromGitHub {
    owner = "matt-kempster";
    repo = "m2c";
    rev = "900b0b6a55307f6cd1270023f641c7380083d8c7";
    hash = "sha256-Lobxj10GM/AeExiX6utYKbzZoyjmHm/J+PG/WbhmorU=";
  };

  postPatch = ''
    substituteInPlace pyproject.toml \
      --replace-fail '"graphviz ~= 0.20.1",' ""
  '';

  pyproject = true;

  build-system = [
    poetry-core
  ];

  dependencies = [
    pycparser
  ];
}

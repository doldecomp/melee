#!/usr/bin/env pwsh

# clone into temp directory for write access
& {
    $inDir = New-Item -ItemType Directory -Path (Join-Path $env:Temp 'Input')
    & git clone 'C:/Input' $inDir
    if ($LASTEXITCODE -ne 0)
    {
        Exit $LASTEXITCODE
    }

    Set-Location $inDir
}

$data = Join-Path $env:LocalAppData 'Melee' -Resolve

# source the venv and restore python requirements
#
# The container image's venv will already have these installed, but if
# requirements.txt has changed since it was built, this will sync the packages.
& {
    & (Join-Path $data 'venv/Scripts/Activate.ps1' -Resolve)

    # https://github.com/pypa/pip/issues/8559#issue-653473661
    & pip3 install --no-cache-dir -r 'requirements.txt' --use-pep517
    if ($LASTEXITCODE -ne 0)
    {
        Exit $LASTEXITCODE
    }
}

& {
    # copy compilers to expected location
    Copy-Item -Path (Join-Path $data 'mwcc_compiler' -Resolve) `
        -Destination 'tools/mwcc_compiler' -Recurse

    # run make
    #
    # Our Makefile doesn't support cmd or PowerShell, so we're calling it from
    # the bash executable installed by MinGW.
    & bash -c 'make -j"$NUMBER_OF_PROCESSORS" "$MAKE_FLAGS"'
    if ($LASTEXITCODE -ne 0)
    {
        Exit $LASTEXITCODE
    }

    # copy to output volume
    Copy-Item -Path 'build/*' -Destination 'C:/Output' -Recurse
}

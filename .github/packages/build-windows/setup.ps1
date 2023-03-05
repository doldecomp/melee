#!/usr/bin/env pwsh

# install packages with scoop
#
# Compared to Chocolatey, scoop is newer and is FOSS (dual Unlicense/MIT).
#
# Winget, while built into Windows, requires Windows Store shenanigans just to
# install and doesn't provide as many packages yet.
#
# It's also not supported on Windows Server, which this container requires:
# https://github.com/microsoft/winget-cli/issues/754#issuecomment-902798802
#
# However, because this container image is meant to smoke test our Windows DX,
# we should revisit winget later when it's more promoted by Microsoft.
& {
    Set-ExecutionPolicy RemoteSigned -Scope CurrentUser
    Invoke-RestMethod get.scoop.sh | Invoke-Expression

    & scoop install `
        git `
        python `
        mingw
    if ($LASTEXITCODE -ne 0)
    {
        Exit $LASTEXITCODE
    }
}

$data = New-Item -Path "$env:LocalAppData/Melee" -ItemType Directory

& {
    # create a venv for our Python tooling
    $venvPath = Join-Path $data 'venv'
    & python -m venv --upgrade-deps $venvPath
    if ($LASTEXITCODE -ne 0)
    {
        Exit $LASTEXITCODE
    }

    & (Join-Path $venvPath 'Scripts/Activate.ps1' -Resolve)

    # https://github.com/pypa/pip/issues/8559#issue-653473661
    & pip install --no-cache-dir -r 'C:/Windows/Temp/requirements.txt' --use-pep517
    if ($LASTEXITCODE -ne 0)
    {
        Exit $LASTEXITCODE
    }
}

# download and save melee compilers
& {
    $tmp = New-TemporaryFile
    Invoke-WebRequest -Uri "$env:MELEE_COMPILERS_URL" -OutFile $tmp
    # Expand-Archive won't unzip it if its extension isn't .zip lol
    $zip = Rename-Item $tmp -NewName ($tmp.BaseName + '.zip') -PassThru

    $dir = New-Item -ItemType Directory `
        -Path (Join-Path $env:Temp 'MELEE_COMPILERS')

    Expand-Archive -Path $zip -DestinationPath $dir

    $path = Get-ChildItem -Path $dir.FullName | `
            Select-Object -ExpandProperty FullName
    Copy-Item -Path $path -Destination "$data/mwcc_compiler" -Recurse

    Remove-Item -Force $zip
    Remove-Item -Recurse -Force $dir
}

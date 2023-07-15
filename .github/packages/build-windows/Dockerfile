# Unlike our Linux packages, the only reason for this to exist is to smoke test
# our developer experience for Windows users. As such, it does things like install
# a Python venv and our requirements.txt packages, without actually using them,
# and it doesn't generate our documentation pages or output PROGRESS.md.
# It's also excruciatingly slow, both to build the package and to build melee.
#
# Note: Microsoft does not offer a "latest" (or equivalent) tag, instead they
# offer year-specific LTSC releases that seem to roughly match the cadence of
# Visual Studio releases (every three years or so).
FROM mcr.microsoft.com/windows/servercore:ltsc2022 AS build-windows
# PowerShell 5.1 is included in Windows Server and should mirror a fresh
# install of Windows 10/11. By default, PowerShell doesn't exit when a command
# fails so we need to set those options. Also note that even with these
# settings, it will not exit when a native command (exe) fails, so in the
# scripts we need to check the error code and exit if it's not 0, every time.
# There is an experimental fix to this but it's only available in PowerShell 7:
# https://github.com/PowerShell/PowerShell/issues/3996
SHELL [ "powershell", "-command", \
    "Set-StrictMode -Version 'Latest'; \
    $ErrorActionPreference = 'Stop';" ]
# "C:/Windows/system32/WindowsPowerShell/v1.0/" is on PATH by default
COPY .github/packages/build-windows/setup.ps1 \
    C:/Windows/system32/WindowsPowerShell/v1.0/
COPY .github/packages/build-windows/entrypoint.ps1 \
    C:/Windows/system32/WindowsPowerShell/v1.0/
COPY requirements.txt C:/Windows/Temp
# on Windows we support a fully unprivileged installation
RUN net user melee /add; \
    # grant melee user read access to requirements.txt
    icacls 'C:/Windows/Temp/requirements.txt' /grant 'melee:(R)';
USER melee
ENV MELEE_COMPILERS_URL="https://cdn.discordapp.com/attachments/727909624342380615/1129879865433264158/MELEE_COMPILERS_N.zip"
RUN setup.ps1
VOLUME [ "C:/Input", "C:/Output" ]
ENTRYPOINT entrypoint.ps1

#!/bin/bash

. updateAntivirus.properties
function update
{
cd $path
echo $blacklist
echo $whitelist
curl -L $blacklist > blacklist   //blacklist
curl -L $whitelist > whitelist //whitelist

}

update

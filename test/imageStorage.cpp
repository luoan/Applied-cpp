#include "imageStorage.h"
#include "image/../exception.h"

apImageStorageBase::apImageStorageBase () { }

apImageStorageBase::apImageStorageBase (const apRect& boundary) : boundary_(boundary)
{ }

apImageStorageBase::~apImageStorageBase ()
{ }



#ifndef PlistDataParser_h__
#define PlistDataParser_h__

#include "../DragonBones.h"
#include "../parsers/dbtinyxml2.h"
#include "../parsers/BaseDataParser.h"

NAME_SPACE_DRAGON_BONES_BEGIN
class PlistDataParser
{
public:
	virtual TextureAtlasData* parseTextureAtlasFile(const std::string& plist) const;
};
NAME_SPACE_DRAGON_BONES_END
#endif // PlistDataParser_h__

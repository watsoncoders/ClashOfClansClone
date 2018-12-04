#include "PlistDataParser.h"
#include "cocos2d.h"
USING_NS_CC;
NAME_SPACE_DRAGON_BONES_BEGIN

TextureAtlasData* PlistDataParser::parseTextureAtlasFile(const std::string& plist) const
{

	std::string fullPath = FileUtils::getInstance()->fullPathForFilename(plist);
	if (fullPath.empty())
	{
		cocos2d::log("Error dragon bones parseTextureAtlasFile: %s not found", plist.c_str());
	}
	
	ValueMap dictionary = FileUtils::getInstance()->getValueMapFromFile(fullPath);

	ValueMap& framesDict = dictionary["frames"].asValueMap();
	int format = 0;
	cocos2d::Size textureSize;
	// get the format
	if (dictionary.find("metadata") != dictionary.end())
	{
		ValueMap& metadataDict = dictionary["metadata"].asValueMap();
		format = metadataDict["format"].asInt();
		textureSize = cocos2d::SizeFromString(metadataDict["size"].asString());
	}

	TextureAtlasData *textureAtlasData = new TextureAtlasData();

	// check the format
	CCASSERT(format >= 0 && format <= 3, "format is not supported for SpriteFrameCache addSpriteFramesWithDictionary:textureFilename:");

	for (auto iter = framesDict.begin(); iter != framesDict.end(); ++iter)
	{
		ValueMap& frameDict = iter->second.asValueMap();
		std::string spriteFrameName = iter->first;
		std::string file_type = "";
		size_t pos_ = spriteFrameName.find_last_of(".");
		if (pos_ != std::string::npos)
		{
			spriteFrameName = spriteFrameName.substr(0,pos_);
		}


		TextureData *textureData = new TextureData();
		textureData->name = spriteFrameName;

		if (format == 0)
		{
			float x = frameDict["x"].asFloat();
			float y = frameDict["y"].asFloat();
			float w = frameDict["width"].asFloat();
			float h = frameDict["height"].asFloat();
			float ox = frameDict["offsetX"].asFloat();
			float oy = frameDict["offsetY"].asFloat();
			int ow = frameDict["originalWidth"].asInt();
			int oh = frameDict["originalHeight"].asInt();
			// check ow/oh
			if (!ow || !oh)
			{
				CCLOGWARN("cocos2d: WARNING: originalWidth/Height not found on the SpriteFrame. AnchorPoint won't work as expected. Regenrate the .plist");
			}
			// abs ow/oh
			ow = abs(ow);
			oh = abs(oh);
			// create frame
			textureData->rotated = false;
			textureData->region.x = x;
			textureData->region.y = y;
			textureData->region.width = w;
			textureData->region.height = h;

			textureData->frame = new Rectangle();
			textureData->frame->x = ox - (ow - w) / 2;
			textureData->frame->y = -oy - oh / 2 + h / 2;
			textureData->frame->width = ow;
			textureData->frame->height = oh;
		}
		else if (format == 1 || format == 2)
		{
			Rect frame = RectFromString(frameDict["frame"].asString());
			bool rotated = false;

			// rotation
			if (format == 2)
			{
				rotated = frameDict["rotated"].asBool();
			}

			Vec2 offset = PointFromString(frameDict["offset"].asString());
			Size sourceSize = SizeFromString(frameDict["sourceSize"].asString());

			// create frame
			textureData->rotated = rotated;
			textureData->region.x = frame.origin.x;
			textureData->region.y = frame.origin.y;
			textureData->region.width = rotated ? frame.size.height : frame.size.width;
			textureData->region.height = rotated ? frame.size.width : frame.size.height;

			textureData->frame = new Rectangle();
			textureData->frame->x = offset.x - (sourceSize.width - frame.size.width) / 2;
			textureData->frame->y = - offset.y - sourceSize.height / 2 + frame.size.height / 2;
			textureData->frame->width = sourceSize.width;
			textureData->frame->height = sourceSize.height;
		}
		else if (format == 3)
		{
			// get values
			Size spriteSize = SizeFromString(frameDict["spriteSize"].asString());
			Vec2 spriteOffset = PointFromString(frameDict["spriteOffset"].asString());
			Size spriteSourceSize = SizeFromString(frameDict["spriteSourceSize"].asString());
			Rect textureRect = RectFromString(frameDict["textureRect"].asString());
			bool textureRotated = frameDict["textureRotated"].asBool();

			/// get aliases

			// create frame
			textureData->rotated = textureRotated;
			textureData->region.x = textureRect.origin.x;
			textureData->region.y = textureRect.origin.y;
			textureData->region.width = textureRect.size.width;
			textureData->region.height = textureRect.size.height;

			textureData->frame = new Rectangle();
			textureData->frame->x = spriteOffset.x - (spriteSourceSize.width - textureRect.size.width) / 2;
			textureData->frame->y = -spriteOffset.y - spriteSourceSize.height / 2 + textureRect.size.height / 2;
			textureData->frame->width = spriteSourceSize.width;
			textureData->frame->height = spriteSourceSize.height;
		}

		// add sprite frame
		textureAtlasData->textureDataList.push_back(textureData);
	}

	return textureAtlasData;
}
NAME_SPACE_DRAGON_BONES_END
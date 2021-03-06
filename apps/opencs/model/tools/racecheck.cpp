
#include "racecheck.hpp"

#include <sstream>

#include <components/esm/loadrace.hpp>

#include "../world/universalid.hpp"

void CSMTools::RaceCheckStage::performPerRecord (int stage, std::vector<std::string>& messages)
{
    const ESM::Race& race = mRaces.getRecord (stage).get();

    CSMWorld::UniversalId id (CSMWorld::UniversalId::Type_Race, race.mId);

    // test for empty name and description
    if (race.mName.empty())
        messages.push_back (id.toString() + "|" + race.mId + " has an empty name");

    if (race.mDescription.empty())
        messages.push_back (id.toString() + "|" + race.mId + " has an empty description");

    // test for positive height
    if (race.mData.mHeight.mMale<=0)
        messages.push_back (id.toString() + "|male " + race.mId + " has non-positive height");

    if (race.mData.mHeight.mFemale<=0)
        messages.push_back (id.toString() + "|female " + race.mId + " has non-positive height");

    // test for non-negative weight
    if (race.mData.mWeight.mMale<0)
        messages.push_back (id.toString() + "|male " + race.mId + " has negative weight");

    if (race.mData.mWeight.mFemale<0)
        messages.push_back (id.toString() + "|female " + race.mId + " has negative weight");

    // remember playable flag
    if (race.mData.mFlags & 0x1)
        mPlayable = true;

    /// \todo check data members that can't be edited in the table view
}

void CSMTools::RaceCheckStage::performFinal (std::vector<std::string>& messages)
{
    CSMWorld::UniversalId id (CSMWorld::UniversalId::Type_Races);

    if (!mPlayable)
        messages.push_back (id.toString() + "|No playable race");
}

CSMTools::RaceCheckStage::RaceCheckStage (const CSMWorld::IdCollection<ESM::Race>& races)
: mRaces (races), mPlayable (false)
{}

int CSMTools::RaceCheckStage::setup()
{
    mPlayable = false;
    return mRaces.getSize()+1;
}

void CSMTools::RaceCheckStage::perform (int stage, std::vector<std::string>& messages)
{
    if (stage==mRaces.getSize())
        performFinal (messages);
    else
        performPerRecord (stage, messages);
}
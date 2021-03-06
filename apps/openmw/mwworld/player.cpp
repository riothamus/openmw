
#include "player.hpp"

#include "../mwbase/environment.hpp"

#include "../mwworld/ptr.hpp"

#include "../mwmechanics/movement.hpp"
#include "../mwmechanics/npcstats.hpp"

#include "class.hpp"

namespace MWWorld
{
    Player::Player (const ESM::NPC *player, const MWBase::World& world)
      : mCellStore(0),
        mAutoMove(false),
        mForwardBackward (0)
    {
        mPlayer.mBase = player;
        mPlayer.mRef.mRefID = "player";

        float* playerPos = mPlayer.mData.getPosition().pos;
        playerPos[0] = playerPos[1] = playerPos[2] = 0;
    }

    void Player::set(const ESM::NPC *player)
    {
        mPlayer.mBase = player;

        float* playerPos = mPlayer.mData.getPosition().pos;
        playerPos[0] = playerPos[1] = playerPos[2] = 0;
    }

    void Player::setCell (MWWorld::CellStore *cellStore)
    {
        mCellStore = cellStore;
    }

    MWWorld::Ptr Player::getPlayer()
    {
        MWWorld::Ptr ptr (&mPlayer, mCellStore);
        return ptr;
    }

    void Player::setBirthSign (const std::string &sign)
    {
        mSign = sign;
    }

    const std::string& Player::getBirthSign() const
    {
        return mSign;
    }

    void Player::setDrawState (MWMechanics::DrawState_ state)
    {
         MWWorld::Ptr ptr = getPlayer();
         MWWorld::Class::get(ptr).getNpcStats(ptr).setDrawState (state);
    }

    bool Player::getAutoMove() const
    {
        return mAutoMove;
    }

    void Player::setAutoMove (bool enable)
    {
        MWWorld::Ptr ptr = getPlayer();

        mAutoMove = enable;

        int value = mForwardBackward;

        if (mAutoMove)
            value = 1;

        MWWorld::Class::get (ptr).getMovementSettings (ptr).mPosition[1] = value;
    }

    void Player::setLeftRight (int value)
    {
        MWWorld::Ptr ptr = getPlayer();

        MWWorld::Class::get (ptr).getMovementSettings (ptr).mPosition[0] = value;
    }

    void Player::setForwardBackward (int value)
    {
        MWWorld::Ptr ptr = getPlayer();

        mForwardBackward = value;

        if (mAutoMove)
            value = 1;

        MWWorld::Class::get (ptr).getMovementSettings (ptr).mPosition[1] = value;
    }

    void Player::setUpDown(int value)
    {
        MWWorld::Ptr ptr = getPlayer();

        MWWorld::Class::get (ptr).getMovementSettings (ptr).mPosition[2] = value;
    }

    void Player::setRunState(bool run)
    {
        MWWorld::Ptr ptr = getPlayer();
        MWWorld::Class::get(ptr).setStance(ptr, MWWorld::Class::Run, run);
    }

    void Player::setSneak(bool sneak)
    {
        MWWorld::Ptr ptr = getPlayer();

        MWWorld::Class::get (ptr).setStance (ptr, MWWorld::Class::Sneak, sneak);
    }

    void Player::setYaw(float yaw)
    {
        MWWorld::Ptr ptr = getPlayer();
        MWWorld::Class::get(ptr).getMovementSettings(ptr).mRotation[2] = yaw;
    }
    void Player::setPitch(float pitch)
    {
        MWWorld::Ptr ptr = getPlayer();
        MWWorld::Class::get(ptr).getMovementSettings(ptr).mRotation[0] = pitch;
    }
    void Player::setRoll(float roll)
    {
        MWWorld::Ptr ptr = getPlayer();
        MWWorld::Class::get(ptr).getMovementSettings(ptr).mRotation[1] = roll;
    }

    MWMechanics::DrawState_ Player::getDrawState()
    {
         MWWorld::Ptr ptr = getPlayer();
         return MWWorld::Class::get(ptr).getNpcStats(ptr).getDrawState();
    }
}

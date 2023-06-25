#pragma once

namespace usl
{
	/// <summary>
		/// �����蔻��̌��ʂ�Ԃ�
		/// </summary>
		/// <param name="aObjPos">��ڂ̃I�u�W�F�N�g�̈ʒu</param>
		/// <param name="aObjSizeX">��ڂ̃I�u�W�F�N�g�̃T�C�Y��X�̒l</param>
		/// <param name="aObjSizeY">��ڂ̃I�u�W�F�N�g�̃T�C�Y��Y�̒l</param>
		/// <param name="bObjPos">��ڂ̃I�u�W�F�N�g�̈ʒu</param>
		/// <param name="bObjSizeX">��ڂ̃I�u�W�F�N�g�̃T�C�Y��X�̒l</param>
		/// <param name="bObjSizeY">��ڂ̃I�u�W�F�N�g�̃T�C�Y��Y�̒l</param>
		/// <returns></returns>
	bool rectAngleAndRectAngleHitDetect(tnl::Vector3 aObjPos, float aObjSizeX, float aObjSizeY, tnl::Vector3 bObjPos, float bObjSizeX, float bObjSizeY)
	{
		tnl::Vector3 aObjCenterPos = { aObjPos.x + aObjSizeX / 2, aObjPos.y + aObjSizeY / 2, 0 };
		tnl::Vector3 bObjCenterPos = { bObjPos.x + bObjSizeX / 2, bObjPos.y + bObjSizeY / 2, 0 };

		auto xDiff = std::abs(aObjCenterPos.x - bObjCenterPos.x);
		auto yDiff = std::abs(aObjCenterPos.y - bObjCenterPos.y);

		if (yDiff < aObjSizeY / 2 + bObjSizeY / 2 && xDiff < aObjSizeX / 2 + bObjSizeX / 2) {
			return true;
		}
		else {
			return false;
		}
	}

}
class CollisionDetect
{
public:
	
};


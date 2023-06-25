#pragma once

namespace usl
{
	/// <summary>
		/// 当たり判定の結果を返す
		/// </summary>
		/// <param name="aObjPos">一つ目のオブジェクトの位置</param>
		/// <param name="aObjSizeX">一つ目のオブジェクトのサイズのXの値</param>
		/// <param name="aObjSizeY">一つ目のオブジェクトのサイズのYの値</param>
		/// <param name="bObjPos">二つ目のオブジェクトの位置</param>
		/// <param name="bObjSizeX">二つ目のオブジェクトのサイズのXの値</param>
		/// <param name="bObjSizeY">二つ目のオブジェクトのサイズのYの値</param>
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


#include "box2d\b2_world_callbacks.h"
#include "Delegate.h"
#include "GameObject.h"

class ContactListener : public b2ContactListener {

private:

	struct DelegateAndParam {

		DelegateAndParam(GameObject* Noriginal, Delegate<GameObject*>* Deleg, GameObject* paramM) {
			original = Noriginal;
			del = Deleg;
			param = paramM;
		}

		GameObject* original;
		Delegate<GameObject*>* del;
		GameObject* param;
	};

	std::vector<DelegateAndParam> m_delList;

	bool IsValidObject(GameObject* objA, GameObject* ObjB);
	bool IsValidComponent(class CollisionComponent* compA, CollisionComponent* compB);

public:
	virtual void BeginContact(b2Contact* contact) override;
	virtual void EndContact(b2Contact* contact) override;

	void ExecuteHandles();
	void AddDel(GameObject* caller,Delegate<GameObject*>* newDel, GameObject* param);
};
#include "IGameObject.h"

enum GhostStates
{
	Chase,
	Frightened,
	Scatter
};

class IGhost:protected IGameObject
{
public:
	void Init(vec3 position, int difficulty) override;
	void Draw() override;
	void ChoseDirection();
	void Move();
	void Update();

	virtual void GetTargetTile(vec2, vec2, vec2) = 0;
protected:
	bool active;
	GhostStates state;
	vec2 scatterTile;
	vec2 targetTile;
};
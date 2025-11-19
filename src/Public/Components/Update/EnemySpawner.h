#pragma once

#include <Components/Update/IUpdateComponent.h>
#include <Core/Common.h>

#include <Components/Update/EnemyController.h>
#include <Components/Renderers/ShapeRenderers/PolygonRenderer.h>

class EnemySpawner : public IUpdateComponent {
public:
	struct Desc {
		float spawnFreq;
		Vec2 spawnMargin;
	};
	explicit EnemySpawner(const Desc desc) {
		_spawnFreq = desc.spawnFreq;
		_spawnMargin = desc.spawnMargin;
	}

private:
	float _spawnFreq = 0.f;
	float _elapsedTime = 0.f;
	Vec2 _spawnMargin = { 0.f, 0.f };
	List<Object*> _enemies;

	void Update(float deltaTime) {
		_elapsedTime += deltaTime;

		if (_elapsedTime >= _spawnFreq) {
			_elapsedTime = 0.f;
			SpawnEnemy();
		}
	}

	void SpawnEnemy() {
		Object* enemy = ObjectManager::RegisterObject(new Object("Enemy"));
		enemy->Position = { 100.f, 100.f };
		enemy->AddComponent(new EnemyController({ 100.f, 180.f, 0.1f, {0.f, 0.f}, {0.f, 0.f} }));
		enemy->AddComponent(new PolygonRenderer(5, 12.f))->FillColor = Color(0.8f, 0.f, 0.2f, 1.f);

		_enemies.push_back(enemy);
	}

public:
	void DisableEnemies() {
		for (int i = 0; i < _enemies.size(); i++)
			_enemies[i]->Enabled = false;
	}
};
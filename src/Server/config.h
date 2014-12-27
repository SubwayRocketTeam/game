#pragma once

namespace config {
	const unsigned short port = 4321;

	const bool gui = true;

	// 게임 시작 시 맵에 뿌려지는 trash 수
	const int start_trash = 10;
	// 죽었을 때 업그레이드 횟수에 곱해져서 뿌려지는 trash
	const int death_upgrade_trash = 10;

	// Repair Area 범위
	const float repair_area_size = 100;

	// 업그레이드 시작 가격
	const int upgrade_cost_start = 10;
	// 업그레이드 가격 증가량
	const int upgrade_cost_delta = 10;
}
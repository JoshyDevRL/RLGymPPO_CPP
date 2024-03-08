#pragma once
//#include "PPO/PPOLearner.h"
//#include "Threading/ThreadAgentManager.h"
#include "Threading/GameInst.h"
#include "Util/WelfordRunningStat.h"
#include "Util/MetricSender.h"
#include "LearnerConfig.h"

namespace RLGPC {

	typedef std::function<void(class Learner*, Report&)> IterationCallback;

	// https://github.com/AechPro/rlgym-ppo/blob/main/rlgym_ppo/learner.py
	class RG_IMEXPORT Learner {
	public:
		LearnerConfig config;

		class PPOLearner* ppo;
		class ThreadAgentManager* agentMgr;
		class ExperienceBuffer* expBuffer;
		EnvCreateFn envCreateFn;
		MetricSender* metricSender;

		int obsSize;
		int actionAmount;

		std::string runID = {};

		uint64_t
			totalTimesteps = 0,
			totalEpochs = 0;
			
		WelfordRunningStat returnStats = WelfordRunningStat(1);

		Learner(EnvCreateFn envCreateFunc, LearnerConfig config);
		void Learn();
		void AddNewExperience(class GameTrajectory& gameTraj);

		std::vector<Report> GetAllGameMetrics();

		void Save();
		void Load();
		void SaveStats(std::filesystem::path path);
		void LoadStats(std::filesystem::path path);

		IterationCallback iterationCallback = NULL;
		StepCallback stepCallback = NULL;

		RG_NO_COPY(Learner);

		~Learner();
	};
}
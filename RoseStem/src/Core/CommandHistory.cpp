#include "CommandHistory.h"

namespace Rose {
	struct CommandHistoryData {
		std::list<Ref<Command>> commandBuffer = std::list<Ref<Command>>();

		int Location = 0;
		int MaxSize = 30;
	};

	static CommandHistoryData s_commandData;


	void CommandHistory::Init()
	{
		s_commandData.commandBuffer.resize(s_commandData.MaxSize);
	}

	void CommandHistory::Clear()
	{
		s_commandData.commandBuffer.clear();
		s_commandData.Location = 0;
	}

	void CommandHistory::Execute(Ref<Command> command)
	{
		s_commandData.Location = 0;
		command->Execute();
		s_commandData.commandBuffer.push_front(command);
	}

	void CommandHistory::Undo()
	{
		if (s_commandData.Location >= s_commandData.MaxSize) {
			RR_CORE_WARN("You have reached the end of the commandBuffer");
			return;
		}
		
		std::list<Ref<Command>>::iterator iterator = s_commandData.commandBuffer.begin();
		for (int i = 0; i < s_commandData.Location; i++) {
			++iterator;
		}
		if (iterator->get() == nullptr) {
			RR_CORE_WARN("Nothing to Undo");
			return;
		}
		iterator->get()->Undo();
		s_commandData.Location++;
	}

	void CommandHistory::Redo()
	{
		if (s_commandData.Location == 0) {
			RR_CORE_WARN("Nothing to Redo");
			return;
		}

		s_commandData.Location--;
		std::list<Ref<Command>>::iterator iterator = s_commandData.commandBuffer.begin();
		for (int i = 0; i < s_commandData.Location; i++) {
			++iterator;
		}
		iterator->get()->Execute();
	}

}


#pragma once
#include "RoseRoot.h"

namespace Rose {
	//Commands are store back to front and when the commandBuffer goes above the max size the back one gets deleted

	class Command {
	public:
		virtual ~Command() = default;

		virtual void Execute() = 0;
		virtual void Undo() = 0;
	};

	template<typename T>
	class ChangeValueCommand : public Command{
	public:
		ChangeValueCommand(T& valToChange, T newVal)
			: m_ValToChange(valToChange), m_NewVal(newVal) {}
		virtual ~ChangeValueCommand() = default;

		virtual void Execute() override {
			m_OldVal = m_ValToChange;
			m_ValToChange = m_NewVal;
		}
		virtual void Undo() override {
			m_ValToChange = m_OldVal;
		}
	private:
		T& m_ValToChange;
		T m_NewVal;
		T m_OldVal;
	};
	
	class CommandHistory {
	public:
		static void Init();

		static void Clear();

		static void Execute(Ref<Command> command);
		static void Undo();
		static void Redo();
	};
}
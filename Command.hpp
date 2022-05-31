class Command {
  virtual void execute() = 0;
  virtual void undo() = 0;
  void redo() {
    this->execute();
  }
};

template <typename T>
class CommandOpenCell : public Command {
private:
  
  T value, pred_value;
  
public:
  // public CommandOpenCell( Model model) : base(state, model){}
  

  virtual void execute() override{

    modele_->openCell(x,y);
    Cell& cell = modele_->getCellRef(x,y);
    this->pred_value = cell.getState();
    
    
  }

  virtual void undo() override{

  }
  
};

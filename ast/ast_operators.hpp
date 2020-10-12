#ifndef ast_operators_hpp
#define ast_operators_hpp

#include <string>
#include <iostream>
#include <cmath>

class Operator
    : public Expression
{

protected:
    ExpressionPtr left;
    ExpressionPtr right;
    Operator(ExpressionPtr _left, ExpressionPtr _right)
        : left(_left)
        , right(_right)
    {}
public:

    ExpressionPtr getLeft() const
    { return left; }

    ExpressionPtr getRight() const
    { return right; }

    virtual double evaluate()
    {

    }
    virtual void translate(std::ostream& outFile, int& indt, std::string sc, std::vector<std::string>& gvars) const{
  	}
};

class NotOperator
    : public Operator
{
private:
  ExpressionPtr operand;
public:
    NotOperator(ExpressionPtr _operand)
        : operand(_operand), Operator(_operand, _operand)
    {

    }
    virtual int getType() {
	return notOp;
	}
  /*virtual double evaluate()
  {
    return ((int) operand->evaluate())--;
  }*/
virtual std::vector<ProgramPtr> getPointers() {
    std::cerr << "getting the pointers of an operand\n";
		std::vector<ProgramPtr> ret;
		ret.push_back(operand);
		return ret;
	}

};
class PostIncrement
    : public Operator
{
private:
  ExpressionPtr operand;
public:
    PostIncrement(ExpressionPtr _operand)
        : operand(_operand), Operator(_operand, _operand)
    {

    }
    /*virtual double evaluate()
    {
      return ((int) operand->evaluate())++;
    }*/
    virtual int getType() {
	return postIncrement;
	}
virtual std::vector<ProgramPtr> getPointers() {
    std::cerr << "getting the pointers of an operand\n";
		std::vector<ProgramPtr> ret;
		ret.push_back(operand);
		return ret;
	}
};

class PostDecrement
    : public Operator
{
private:
  ExpressionPtr operand;
public:
    PostDecrement(ExpressionPtr _operand)
        : operand(_operand), Operator(_operand, _operand)
    {

    }
    virtual int getType() {
	return postDecrement;
	}
  /*virtual double evaluate()
  {
    return ((int) operand->evaluate())--;
  }*/
virtual std::vector<ProgramPtr> getPointers() {
    std::cerr << "getting the pointers of an operand\n";
		std::vector<ProgramPtr> ret;
		ret.push_back(operand);
		return ret;
	}

};

class PreIncrement
    : public Operator
{
private:
  ExpressionPtr operand;
public:
    PreIncrement(ExpressionPtr _operand)
        : operand(_operand), Operator(_operand, _operand)
    {

    }
    virtual int getType() {
	return preIncrement;
	}
  /*virtual double evaluate()
  {
    return ++((int) operand->evaluate());
  }*/
virtual std::vector<ProgramPtr> getPointers() {
    std::cerr << "getting the pointers of an operand\n";
		std::vector<ProgramPtr> ret;
		ret.push_back(operand);
		return ret;
	}

};

class PreDecrement
    : public Operator
{
private:
  ExpressionPtr operand;
public:
    PreDecrement(ExpressionPtr _operand)
        : operand(_operand), Operator(_operand, _operand)
    {

    }
    virtual int getType() {
	return preDecrement;
	}
  /*virtual double evaluate()
  {
    return --((int) operand->evaluate());
  }*/
virtual std::vector<ProgramPtr> getPointers() {
    std::cerr << "getting the pointers of an operand\n";
		std::vector<ProgramPtr> ret;
		ret.push_back(operand);
		return ret;
	}


};

class PlusEquals
    : public Operator
{
private:
public:
    PlusEquals(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {

    }
    virtual int getType() {
	return plusEq;
	}
  /*virtual double evaluate()
  {
    return ++((int) operand->evaluate());
  }*/
virtual std::vector<ProgramPtr> getPointers() {
    std::cerr << "getting the pointers of an operand\n";
		std::vector<ProgramPtr> ret;
		ret.push_back(left);
ret.push_back(right);
		return ret;
	}

};

class MinusEquals
    : public Operator
{
private:

public:
    MinusEquals(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {

    }
    virtual int getType() {
	return minusEq;
	}
  /*virtual double evaluate()
  {
    return ++((int) operand->evaluate());
  }*/
virtual std::vector<ProgramPtr> getPointers() {
    std::cerr << "getting the pointers of an operand\n";
		std::vector<ProgramPtr> ret;
		ret.push_back(left);
ret.push_back(right);
		return ret;
	}

};

class TimesEquals
    : public Operator
{
private:

public:
    TimesEquals(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {

    }
    virtual int getType() {
	return timesEq;
	}
  /*virtual double evaluate()
  {
    return ++((int) operand->evaluate());
  }*/
virtual std::vector<ProgramPtr> getPointers() {
    std::cerr << "getting the pointers of an operand\n";
		std::vector<ProgramPtr> ret;
		ret.push_back(left);
ret.push_back(right);
		return ret;
	}

};

class DivEquals
    : public Operator
{
private:

public:
    DivEquals(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {

    }
    virtual int getType() {
	return divEq;
	}
  /*virtual double evaluate()
  {
    return ++((int) operand->evaluate());
  }*/
virtual std::vector<ProgramPtr> getPointers() {
    std::cerr << "getting the pointers of an operand\n";
		std::vector<ProgramPtr> ret;
		ret.push_back(left);
ret.push_back(right);
		return ret;
	}

};

class ModEquals
    : public Operator
{
private:

public:
    ModEquals(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {

    }
    virtual int getType() {
	return modEq;
	}
  /*virtual double evaluate()
  {
    return ++((int) operand->evaluate());
  }*/
virtual std::vector<ProgramPtr> getPointers() {
    std::cerr << "getting the pointers of an operand\n";
		std::vector<ProgramPtr> ret;
		ret.push_back(left);
ret.push_back(right);
		return ret;
	}

};

class AndEquals
    : public Operator
{
private:

public:
    AndEquals(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {

    }
    virtual int getType() {
	return andEq;
	}
  /*virtual double evaluate()
  {
    return ++((int) operand->evaluate());
  }*/
virtual std::vector<ProgramPtr> getPointers() {
    std::cerr << "getting the pointers of an operand\n";
		std::vector<ProgramPtr> ret;
		ret.push_back(left);
ret.push_back(right);
		return ret;
	}

};

class OrEquals
    : public Operator
{
private:

public:
    OrEquals(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {

    }
    virtual int getType() {
	return orEq;
	}
  /*virtual double evaluate()
  {
    return ++((int) operand->evaluate());
  }*/
virtual std::vector<ProgramPtr> getPointers() {
    std::cerr << "getting the pointers of an operand\n";
		std::vector<ProgramPtr> ret;
		ret.push_back(left);
ret.push_back(right);
		return ret;
	}
};

class XorEquals
    : public Operator
{
private:

public:
    XorEquals(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {

    }
    virtual int getType() {
	return xorEq;
	}
  /*virtual double evaluate()
  {
    return ++((int) operand->evaluate());
  }*/
virtual std::vector<ProgramPtr> getPointers() {
    std::cerr << "getting the pointers of an operand\n";
		std::vector<ProgramPtr> ret;
		ret.push_back(left);
ret.push_back(right);
		return ret;
	}

};

class LShiftEquals
    : public Operator
{
private:

public:
    LShiftEquals(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {

    }
    virtual int getType() {
	return lShiftEq;
	}
  /*virtual double evaluate()
  {
    return ++((int) operand->evaluate());
  }*/
virtual std::vector<ProgramPtr> getPointers() {
    std::cerr << "getting the pointers of an operand\n";
		std::vector<ProgramPtr> ret;
		ret.push_back(left);
ret.push_back(right);
		return ret;
	}

};

class RShiftEquals
    : public Operator
{
private:

public:
    RShiftEquals(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {

    }
    virtual int getType() {
	return rShiftEq;
	}
  /*virtual double evaluate()
  {
    return ++((int) operand->evaluate());
  }*/
virtual std::vector<ProgramPtr> getPointers() {
    std::cerr << "getting the pointers of an operand\n";
		std::vector<ProgramPtr> ret;
		ret.push_back(left);
ret.push_back(right);
		return ret;
	}

};

class AddOperator
    : public Operator
{
public:
    AddOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}
    virtual int getType() {
	return addition;
	}
  virtual double evaluate()
  {
    return  left->evaluate() +  right->evaluate();
  }
virtual std::vector<ProgramPtr> getPointers() {
		std::vector<ProgramPtr> ret;
		ret.push_back(getLeft());
		ret.push_back(getRight());
		return ret;
	}

    virtual void translate(std::ostream& outFile, int& indt, std::string sc, std::vector<std::string>& gvars) const{
  		left->translate(outFile, indt, sc, gvars);
      outFile<<" + ";
      right->translate(outFile, indt, sc, gvars);
  	}
};

class SubOperator
    : public Operator
{
public:
    SubOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}
     virtual int getType() {
	return subtraction;
	}
	virtual std::vector<ProgramPtr> getPointers() {
		std::vector<ProgramPtr> ret;
		ret.push_back(getLeft());
		ret.push_back(getRight());
		return ret;
	}

  virtual double evaluate()
  {
    return  left->evaluate() -  right->evaluate();
  }


    virtual void translate(std::ostream& outFile, int& indt, std::string sc, std::vector<std::string>& gvars) const{
  		left->translate(outFile, indt, sc, gvars);
      outFile<<" - ";
      right->translate(outFile, indt, sc, gvars);
  	}

};


class MulOperator
    : public Operator
{
public:
    MulOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}
	virtual int getType() {
	return multiplication;
	}
	virtual std::vector<ProgramPtr> getPointers() {
		std::vector<ProgramPtr> ret;
		ret.push_back(getLeft());
		ret.push_back(getRight());
		return ret;
	}


  virtual double evaluate()
  {
    return  left->evaluate() *  right->evaluate();
  }

    virtual void translate(std::ostream& outFile, int& indt, std::string sc, std::vector<std::string>& gvars) const{
      outFile<<"(";
  		left->translate(outFile, indt, sc, gvars);
      outFile<<" * ";
      right->translate(outFile, indt, sc, gvars);
      outFile<<")";
  	}

};

class DivOperator
    : public Operator
{
public:
    DivOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}
	 virtual int getType() {
	return division;
	}
	virtual std::vector<ProgramPtr> getPointers() {
		std::vector<ProgramPtr> ret;
		ret.push_back(getLeft());
		ret.push_back(getRight());
		return ret;
	}

  virtual double evaluate()
  {
    return  ((int)left->evaluate()) /  ((int)right->evaluate());
  }


    virtual void translate(std::ostream& outFile, int& indt, std::string sc, std::vector<std::string>& gvars) const{
      outFile<<"(";
  		left->translate(outFile, indt, sc, gvars);
      outFile<<" / ";
      right->translate(outFile, indt, sc, gvars);
      outFile<<")";
  	}
};

class ExpOperator
    : public Operator
{
public:
    ExpOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}


    virtual void translate(std::ostream& outFile, int& indt, std::string sc, std::vector<std::string>& gvars) const{
  		left->translate(outFile, indt, sc, gvars);
      outFile<<" ** ";
      right->translate(outFile, indt, sc, gvars);
  	}
};

class ltOperator
    : public Operator
{
public:
    ltOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}
	 virtual int getType() {
	return ltOp;
	}
	virtual std::vector<ProgramPtr> getPointers() {
		std::vector<ProgramPtr> ret;
		ret.push_back(getLeft());
		ret.push_back(getRight());
		return ret;
	}

  virtual double evaluate()
  {
    return  ((int)left->evaluate()) <  ((int)right->evaluate());
  }


    virtual void translate(std::ostream& outFile, int& indt, std::string sc, std::vector<std::string>& gvars) const{
  		left->translate(outFile, indt, sc, gvars);
      outFile<<" < ";
      right->translate(outFile, indt, sc, gvars);
  	}
};

class lteOperator
    : public Operator
{
	public:
    lteOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}
	 virtual int getType() {
	return lteOp;
	}
	virtual std::vector<ProgramPtr> getPointers() {
		std::vector<ProgramPtr> ret;
		ret.push_back(getLeft());
		ret.push_back(getRight());
		return ret;
	}

  virtual double evaluate()
  {
    return  ((int)left->evaluate()) <=  ((int)right->evaluate());
  }

    virtual void translate(std::ostream& outFile, int& indt, std::string sc, std::vector<std::string>& gvars) const{
  		left->translate(outFile, indt, sc, gvars);
      outFile<<" <= ";
      right->translate(outFile, indt, sc, gvars);
  	}

};

class gtOperator
    : public Operator
{
 public:
    gtOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}
	 virtual int getType() {
	return gtOp;
	}
	virtual std::vector<ProgramPtr> getPointers() {
		std::vector<ProgramPtr> ret;
		ret.push_back(getLeft());
		ret.push_back(getRight());
		return ret;
	}

  virtual double evaluate()
  {
    return  ((int)left->evaluate()) > ((int)right->evaluate());
  }


    virtual void translate(std::ostream& outFile, int& indt, std::string sc, std::vector<std::string>& gvars) const{
  		left->translate(outFile, indt, sc, gvars);
      outFile<<" > ";
      right->translate(outFile, indt, sc, gvars);
  	}
};

class gteOperator
    : public Operator
{
  public:
    gteOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}
	 virtual int getType() {
	return gteOp;
	}
	virtual std::vector<ProgramPtr> getPointers() {
		std::vector<ProgramPtr> ret;
		ret.push_back(getLeft());
		ret.push_back(getRight());
		return ret;
	}

  virtual double evaluate()
  {
    return  ((int)left->evaluate()) >=  ((int)right->evaluate());
  }

    virtual void translate(std::ostream& outFile, int& indt, std::string sc, std::vector<std::string>& gvars) const{
  		left->translate(outFile, indt, sc, gvars);
      outFile<<" >= ";
      right->translate(outFile, indt, sc, gvars);
  	}
};
class lShiftOperator
    : public Operator
{
    public:
    lShiftOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}
	 virtual int getType() {
	return lShiftOp;
	}
	virtual std::vector<ProgramPtr> getPointers() {
		std::vector<ProgramPtr> ret;
		ret.push_back(getLeft());
		ret.push_back(getRight());
		return ret;
	}

  virtual double evaluate()
  {
    return  ((int)left->evaluate()) <<  ((int)right->evaluate());
  }


    virtual void translate(std::ostream& outFile, int& indt, std::string sc, std::vector<std::string>& gvars) const{
  		left->translate(outFile, indt, sc, gvars);
      outFile<<" << ";
      right->translate(outFile, indt, sc, gvars);
  	}
};
class rShiftOperator
    : public Operator
{
	public:
    rShiftOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}
	 virtual int getType() {
	return rShiftOp;
	}
	virtual std::vector<ProgramPtr> getPointers() {
		std::vector<ProgramPtr> ret;
		ret.push_back(getLeft());
		ret.push_back(getRight());
		return ret;
	}


  virtual double evaluate()
  {
    return  ((int)left->evaluate()) >>  ((int)right->evaluate());
  }

    virtual void translate(std::ostream& outFile, int& indt, std::string sc, std::vector<std::string>& gvars) const{
  		left->translate(outFile, indt, sc, gvars);
      outFile<<" >> ";
      right->translate(outFile, indt, sc, gvars);
  	}
};

class moduloOperator
    : public Operator
{
	public:
    moduloOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}
	 virtual int getType() {
	return moduloOp;
	}
	virtual std::vector<ProgramPtr> getPointers() {
		std::vector<ProgramPtr> ret;
		ret.push_back(getLeft());
		ret.push_back(getRight());
		return ret;
	}

  virtual double evaluate()
  {
    return  ((int)left->evaluate()) %  ((int)right->evaluate());
  }



    virtual void translate(std::ostream& outFile, int& indt, std::string sc, std::vector<std::string>& gvars) const{
  		left->translate(outFile, indt, sc, gvars);
      outFile<<" % ";
      right->translate(outFile, indt, sc, gvars);
  	}
};

class equalsOperator
    : public Operator
{
	public:
    equalsOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}
	 virtual int getType() {
	return equals;
	}
	virtual std::vector<ProgramPtr> getPointers() {
		std::vector<ProgramPtr> ret;
		ret.push_back(getLeft());
		ret.push_back(getRight());
		return ret;
	}

  virtual double evaluate()
  {
    return  ((int)left->evaluate()) ==  ((int)right->evaluate());
  }

    virtual void translate(std::ostream& outFile, int& indt, std::string sc, std::vector<std::string>& gvars) const{
  		left->translate(outFile, indt, sc, gvars);
      outFile<<" == ";
      right->translate(outFile, indt, sc, gvars);
  	}


};

class subscriptOperator
    : public Operator
{
	private:
		std::string pointerName;
		ExpressionPtr offsetExpression;
	public:
    subscriptOperator(std::string _left, ExpressionPtr _right)
        : pointerName(_left) , offsetExpression(_right), Operator(_right, _right)
    {}
	 virtual int getType() {
	return subscript;
	}
	virtual std::vector<ProgramPtr> getPointers() {
		//std::cerr << "getting offset \n";
		std::vector<ProgramPtr> ret;
		ret.push_back(offsetExpression);
		return ret;
	}
	virtual std::vector<std::string> getStrings() {
		std::vector<std::string> ret;
		ret.push_back(pointerName);
		return ret;
	}


};

class NegOperator
    : public Operator
{
private:
  ExpressionPtr expression;
public:
  NegOperator(ExpressionPtr _expression)
      : expression(_expression), Operator(expression, expression)
  {}
 virtual int getType() {
return neg;
}
virtual std::vector<ProgramPtr> getPointers() {
  std::vector<ProgramPtr> ret;
  ret.push_back(expression);
  return ret;
}
virtual double evaluate()
{
  return  -((int)right->evaluate());
}

};

class notEqualOperator
    : public Operator
{
public:
  notEqualOperator(ExpressionPtr _left, ExpressionPtr _right)
      : Operator(_left, _right)
  {}
 virtual int getType() {
return notEqual;
}
virtual std::vector<ProgramPtr> getPointers() {
  std::vector<ProgramPtr> ret;
  ret.push_back(getLeft());
  ret.push_back(getRight());
  return ret;
}
virtual double evaluate()
{
  return  ((int)left->evaluate()) !=  ((int)right->evaluate());
}
virtual void translate(std::ostream& outFile, int& indt, std::string sc, std::vector<std::string>& gvars) const{
  left->translate(outFile, indt, sc, gvars);
  outFile<<" != ";
  right->translate(outFile, indt, sc, gvars);
}

};

class bitWiseAndOperator
    : public Operator
{
public:
  bitWiseAndOperator(ExpressionPtr _left, ExpressionPtr _right)
      : Operator(_left, _right)
  {}
 virtual int getType() {
return bitWiseAnd;
}
virtual double evaluate()
{
  return  ((int)left->evaluate()) &  ((int)right->evaluate());
}
virtual std::vector<ProgramPtr> getPointers() {
  std::vector<ProgramPtr> ret;
  ret.push_back(getLeft());
  ret.push_back(getRight());
  return ret;
}
virtual void translate(std::ostream& outFile, int& indt, std::string sc, std::vector<std::string>& gvars) const{
  left->translate(outFile, indt, sc, gvars);
  outFile<<" & ";
  right->translate(outFile, indt, sc, gvars);
}

};

class bitWiseEorOperator
    : public Operator
{
public:
  bitWiseEorOperator(ExpressionPtr _left, ExpressionPtr _right)
      : Operator(_left, _right)
  {}
 virtual int getType() {
return bitWiseEor;
}
virtual std::vector<ProgramPtr> getPointers() {
  std::vector<ProgramPtr> ret;
  ret.push_back(getLeft());
  ret.push_back(getRight());
  return ret;
}
virtual double evaluate()
{
  return  ((int)left->evaluate()) ^  ((int)right->evaluate());
}
virtual void translate(std::ostream& outFile, int& indt, std::string sc, std::vector<std::string>& gvars) const{
  left->translate(outFile, indt, sc, gvars);
  outFile<<" ^ ";
  right->translate(outFile, indt, sc, gvars);
}

};

class bitWiseIorOperator
    : public Operator
{
public:
  bitWiseIorOperator(ExpressionPtr _left, ExpressionPtr _right)
      : Operator(_left, _right)
  {}
 virtual int getType() {
return bitWiseIor;
}
virtual std::vector<ProgramPtr> getPointers() {
  std::vector<ProgramPtr> ret;
  ret.push_back(getLeft());
  ret.push_back(getRight());
  return ret;
}
virtual double evaluate()
{
  return  ((int)left->evaluate()) |  ((int)right->evaluate());
}
virtual void translate(std::ostream& outFile, int& indt, std::string sc, std::vector<std::string>& gvars) const{
  left->translate(outFile, indt, sc, gvars);
  outFile<<" | ";
  right->translate(outFile, indt, sc, gvars);
}
};

class logicalAndOperator
    : public Operator
{
public:
  logicalAndOperator(ExpressionPtr _left, ExpressionPtr _right)
      : Operator(_left, _right)
  {}
 virtual int getType() {
return logicalAnd;
}
virtual std::vector<ProgramPtr> getPointers() {
  std::vector<ProgramPtr> ret;
  ret.push_back(getLeft());
  ret.push_back(getRight());
  return ret;
}
virtual double evaluate()
{
  return  ((int)left->evaluate()) &&  ((int)right->evaluate());
}
virtual void translate(std::ostream& outFile, int& indt, std::string sc, std::vector<std::string>& gvars) const{
  left->translate(outFile, indt, sc, gvars);
  outFile<<" and ";
  right->translate(outFile, indt, sc, gvars);
}

};

class logicalOrOperator
    : public Operator
{
public:
  logicalOrOperator(ExpressionPtr _left, ExpressionPtr _right)
      : Operator(_left, _right)
  {}
 virtual int getType() {
return logicalOr;
}
virtual std::vector<ProgramPtr> getPointers() {
  std::vector<ProgramPtr> ret;
  ret.push_back(getLeft());
  ret.push_back(getRight());
  return ret;
}
virtual double evaluate()
{
  return  ((int)left->evaluate()) ||  ((int)right->evaluate());
}
virtual void translate(std::ostream& outFile, int& indt, std::string sc, std::vector<std::string>& gvars) const{
  left->translate(outFile, indt, sc, gvars);
  outFile<<" or ";
  right->translate(outFile, indt, sc, gvars);
}
};

#endif

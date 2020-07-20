#include "../inc/LandCal.h"

using namespace std;

void LandCal::showMain()
{
    cout << "1. Add your house Info" << endl;
    cout << "2. Save Data to Excel" << endl;
    cout << "3. Update your house Info" << endl;
	cout << "4. show your house Info and Tax" << endl;
	cout << "6. Exit" << endl << endl;

	cout << "please select number : ";
}

void LandCal::addLandInfo()
{
    cout << "Add Land your info" << endl;
    numoofHouse_++;
    std::shared_ptr<LandTaxCal> landTax = makeLandInfo();
	calTax(landTax);
    landTaxCal.push_back(landTax);
}

int LandCal::getAssementStandardTaxBase(LandTaxCal landTaxCal, double standardTaxBase)
{
	return landTaxCal.getAssementStandardTaxBase();
}

void LandCal::calTax(std::shared_ptr<LandTaxCal> landTaxCal)
{
    cout << "================== " << __func__  << "===================================" << endl;
	// �絵����
	double transferMargin = landTaxCal->getTransferMargin();
	double basicDeduction = landTaxCal->calYearfromDate() * 25e6; // �⺻ ���� 250����

	// �������絵����
	double taxBaseTransferMargin = landTaxCal->getTransferPrice() >= 1e9 ? transferMargin * (landTaxCal->getTransferPrice() - 1e9) / landTaxCal->getTransferPrice() : 0;
	landTaxCal->setTaxBaseTransferMargin(taxBaseTransferMargin);

	// ��⺸�� Ư������
	int longTermDeductuibRate = 1;
	if (numoofHouse_ == 1) longTermDeductuibRate *= landTaxCal->calLongteramHoldingDeductionRate();
	else				   longTermDeductuibRate *= 0;

	taxBaseTransferMargin -= (taxBaseTransferMargin * longTermDeductuibRate);

	// �κ� �絵�ҵ�ݾ�
	if (landTaxCal->getJointTenacy() > 1) {
		taxBaseTransferMargin /= landTaxCal->getJointTenacy();
	}

	// ����ǥ��
	taxBaseTransferMargin -= basicDeduction;

	// �絵 �ҵ漼��
	double trasferMarginTaxRate = landTaxCal->getTrasferMarginTaxRate(taxBaseTransferMargin);

	// ���� ����
	double progressiveTax = landTaxCal->getProgressiveTax(trasferMarginTaxRate);

	// ���鼼��
	double deductionTax = 0; // TBD

	// �絵�ҵ漼 = ����ǥ�� * �絵 �ҵ漼�� - ���� ���� - ���鼼��
	double tax = taxBaseTransferMargin * trasferMarginTaxRate - deductionTax - progressiveTax;

	// ���� �ҵ漼(10%)
	tax *= 1.1;

	// �κ� �絵�ҵ�ݾ�
	if (landTaxCal->getJointTenacy() > 1) {
		tax *= landTaxCal->getJointTenacy();
	}

	landTaxCal->setTax(tax);
}

void LandCal::showLandInfo(const LandCal& landCal)
{
	cout << "================== " << __func__ << "===================================" << endl;
	cout << "number of house : " << landCal.numoofHouse_ << endl;
	for (auto v : landTaxCal) {
		v->show();
	}
}

void LandCal::expectLandRevnue(const LandCal& landCal)
{
	cout << "================== " << __func__ << "===================================" << endl;
	cout << "number of house : " << landCal.numoofHouse_ << endl;
	for (auto v : landTaxCal) {
		v->show();
	}
}

std::shared_ptr<LandTaxCal> LandCal::makeLandInfo()
{
	cout << "================== " << __func__ << "===================================" << endl;
	std::shared_ptr<LandTaxCal> retLandInfo= std::make_shared<LandTaxCal>();
	retLandInfo->addInfo();

	return retLandInfo;
}

void LandCal::saveDatatoExcel()
{
	cout << "================== " << __func__ << "===================================" << endl;
}

void LandCal::updateLandInfo()
{
	cout << "================== " << __func__ << "===================================" << endl;
}
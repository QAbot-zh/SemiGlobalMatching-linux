#pragma once
#include "sgm_types.h"

#ifndef SAFE_DELETE
#define SAFE_DELETE(P) {if(P) delete[](P);(P)=nullptr;}
#endif

namespace sgm_util
{
	//������������ census���߼�
	// census�任

	/**
	 * \brief census�任
	 * \param source	���룬Ӱ������
	 * \param census	�����censusֵ����
	 * \param width		���룬Ӱ���
	 * \param height	���룬Ӱ���
	 */
	void census_transform_5x5(const uint8* source, uint32* census, const sint32& width, const sint32& height);
	void census_transform_9x7(const uint8* source, uint64* census, const sint32& width, const sint32& height);
	// Hamming����
	uint8 Hamming32(const uint32& x, const uint32& y);
	uint8 Hamming64(const uint64& x, const uint64& y);

	/**
	 * \brief ����·���ۺ� �� ��
	 * \param img_data			���룬Ӱ������
	 * \param width				���룬Ӱ���
	 * \param height			���룬Ӱ���
	 * \param min_disparity		���룬��С�Ӳ�
	 * \param max_disparity		���룬����Ӳ�
	 * \param p1				���룬�ͷ���P1
	 * \param p2_init			���룬�ͷ���P2_Init
	 * \param cost_init			���룬��ʼ��������
	 * \param cost_aggr			�����·���ۺϴ�������
	 * \param is_forward		���룬�Ƿ�Ϊ������������Ϊ�����ң�������Ϊ���ҵ���
	 */
	void CostAggregateLeftRight(const uint8* img_data, const sint32& width, const sint32& height, const sint32& min_disparity, const sint32& max_disparity,
		const sint32& p1,const sint32& p2_init, const uint8* cost_init, uint8* cost_aggr, bool is_forward = true);

	/**
	 * \brief ����·���ۺ� �� ��
	 * \param img_data			���룬Ӱ������
	 * \param width				���룬Ӱ���
	 * \param height			���룬Ӱ���
	 * \param min_disparity		���룬��С�Ӳ�
	 * \param max_disparity		���룬����Ӳ�
	 * \param p1				���룬�ͷ���P1
	 * \param p2_init			���룬�ͷ���P2_Init
	 * \param cost_init			���룬��ʼ��������
	 * \param cost_aggr			�����·���ۺϴ�������
	 * \param is_forward		���룬�Ƿ�Ϊ������������Ϊ���ϵ��£�������Ϊ���µ��ϣ�
	 */
	void CostAggregateUpDown(const uint8* img_data, const sint32& width, const sint32& height, const sint32& min_disparity, const sint32& max_disparity,
		const sint32& p1, const sint32& p2_init, const uint8* cost_init, uint8* cost_aggr, bool is_forward = true);

	/**
	 * \brief �Խ���1·���ۺϣ�����<->���£��K �I
	 * \param img_data			���룬Ӱ������
	 * \param width				���룬Ӱ���
	 * \param height			���룬Ӱ���
	 * \param min_disparity		���룬��С�Ӳ�
	 * \param max_disparity		���룬����Ӳ�
	 * \param p1				���룬�ͷ���P1
	 * \param p2_init			���룬�ͷ���P2_Init
	 * \param cost_init			���룬��ʼ��������
	 * \param cost_aggr			�����·���ۺϴ�������
	 * \param is_forward		���룬�Ƿ�Ϊ������������Ϊ�����ϵ����£�������Ϊ�����µ����ϣ�
	 */
	void CostAggregateDagonal_1(const uint8* img_data, const sint32& width, const sint32& height, const sint32& min_disparity, const sint32& max_disparity,
		const sint32& p1, const sint32& p2_init, const uint8* cost_init, uint8* cost_aggr, bool is_forward = true);

	/**
	 * \brief �Խ���2·���ۺϣ�����<->���£��L �J
	 * \param img_data			���룬Ӱ������
	 * \param width				���룬Ӱ���
	 * \param height			���룬Ӱ���
	 * \param min_disparity		���룬��С�Ӳ�
	 * \param max_disparity		���룬����Ӳ�
	 * \param p1				���룬�ͷ���P1
	 * \param p2_init			���룬�ͷ���P2_Init
	 * \param cost_init			���룬��ʼ��������
	 * \param cost_aggr			�����·���ۺϴ�������
	 * \param is_forward		���룬�Ƿ�Ϊ������������Ϊ���ϵ��£�������Ϊ���µ��ϣ�
	 */
	void CostAggregateDagonal_2(const uint8* img_data, const sint32& width, const sint32& height, const sint32& min_disparity, const sint32& max_disparity,
		const sint32& p1, const sint32& p2_init, const uint8* cost_init, uint8* cost_aggr, bool is_forward = true);

	
	/**
	 * \brief ��ֵ�˲�
	 * \param in				���룬Դ���� 
	 * \param out				�����Ŀ������
	 * \param width				���룬����
	 * \param height			���룬�߶�
	 * \param wnd_size			���룬���ڿ���
	 */
	void MedianFilter(const float32* in, float32* out, const sint32& width, const sint32& height, const sint32 wnd_size);


	/**
	 * \brief �޳�С��ͨ��
	 * \param disparity_map		���룬�Ӳ�ͼ 
	 * \param width				���룬����
	 * \param height			���룬�߶�
	 * \param diff_insame		���룬ͬһ��ͨ���ڵľֲ����ز���
	 * \param min_speckle_aera	���룬��С��ͨ�����
	 * \param invalid_val		���룬��Чֵ
	 */
	void RemoveSpeckles(float32* disparity_map, const sint32& width, const sint32& height, const sint32& diff_insame,const uint32& min_speckle_aera, const float32& invalid_val);
}
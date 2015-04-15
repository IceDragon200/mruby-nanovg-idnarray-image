#include <mruby.h>
#include <mruby/data.h>
#include "mrb/idnarray/narray.hxx"
#include "mrb/nvg/context.h"

static inline NVGcontext*
get_context(mrb_state *mrb, mrb_value self)
{
  return (NVGcontext*)mrb_data_get_ptr(mrb, self, &mrb_nvg_context_type);
}

/* @!class Nanovg::Context
 * @!method create_image_mem_narray(flags, data)
 *   @param [Integer] flags
 *   @param [NArray] data
 *   @return [Integer]
 */
static mrb_value
nvg_context_create_image_mem_narray(mrb_state *mrb, mrb_value self)
{
  NVGcontext *context;
  mrb_int flags;
  NArray *narray;
  int image;
  mrb_get_args(mrb, "id", &flags, &narray, &mrb_idnarray_type);
  mrb_narray_check_type(mrb, narray, NARRAY_UINT8);
  context = get_context(mrb, self);
  image = nvgCreateImageMem(context, flags, (uint8_t*)narray->data, narray->memsize);
  return mrb_fixnum_value(image);
}

/* @!class Nanovg::Context
 * @!method create_image_rgba_narray(w, h, flags, data)
 *   @param [Integer] w  width
 *   @param [Integer] h  height
 *   @param [Integer] flags  NVGimageFlags
 *   @param [NArray] data
 *   @return [Integer]
 */
static mrb_value
nvg_context_create_image_rgba_narray(mrb_state *mrb, mrb_value self)
{
  NVGcontext *context;
  mrb_int w;
  mrb_int h;
  mrb_int flags;
  NArray *narray;
  int image;
  mrb_get_args(mrb, "iiid", &w, &h, &flags, &narray, &mrb_idnarray_type);
  mrb_narray_check_type(mrb, narray, NARRAY_UINT8);
  context = get_context(mrb, self);
  image = nvgCreateImageRGBA(context, w, h, flags, (uint8_t*)narray->data);
  return mrb_fixnum_value(image);
}

/* @!class Nanovg::Context
 * @!method update_image_narray(image, data)
 *   @param [Integer] image
 *   @param [NArray] data
 *   @return [Integer]
 */
static mrb_value
nvg_context_update_image_narray(mrb_state *mrb, mrb_value self)
{
  NVGcontext *context;
  mrb_int image;
  NArray *narray;
  mrb_get_args(mrb, "id", &image, &narray, &mrb_idnarray_type);
  mrb_narray_check_type(mrb, narray, NARRAY_UINT8);
  context = get_context(mrb, self);
  nvgUpdateImage(context, image, (uint8_t*)narray->data);
  return mrb_fixnum_value(image);
}

extern "C" void
mrb_mruby_nanovg_idnarray_image_gem_init(mrb_state *mrb)
{
  struct RClass *nanovg_module = mrb_module_get(mrb, "Nanovg");
  struct RClass *nanovg_context_class = mrb_class_get_under(mrb, nanovg_module, "Context");

  mrb_define_method(mrb, nanovg_context_class, "create_image_mem_narray",  nvg_context_create_image_mem_narray,  MRB_ARGS_REQ(2));
  mrb_define_method(mrb, nanovg_context_class, "create_image_rgba_narray", nvg_context_create_image_rgba_narray, MRB_ARGS_REQ(4));
  mrb_define_method(mrb, nanovg_context_class, "update_image_narray",      nvg_context_update_image_narray,      MRB_ARGS_REQ(2));
}

extern "C" void
mrb_mruby_nanovg_idnarray_image_gem_final(mrb_state *mrb)
{
}
